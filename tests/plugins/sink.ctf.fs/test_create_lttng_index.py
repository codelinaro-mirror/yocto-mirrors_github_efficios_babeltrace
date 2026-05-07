# SPDX-FileCopyrightText: 2026 EfficiOS Inc.
# SPDX-License-Identifier: GPL-2.0-only

import types
import struct
import collections

import bt2
import pytest
import bt_tests_utils as btu

_LTTNG_IDX_MAGIC = 0xC1F1DCC1

_IdxHeader = collections.namedtuple(
    "_IdxHeader", ["magic", "major", "minor", "entry_size"]
)

_IdxEntry = collections.namedtuple(
    "_IdxEntry",
    [
        "offset",
        "packet_size",
        "content_size",
        "timestamp_begin",
        "timestamp_end",
        "events_discarded",
        "stream_id",
        "stream_instance_id",
        "packet_seq_num",
    ],
)


# Parses the LTTng index file at `path` and returns its header
# (`_IdxHeader`) and the list of its entries (`_IdxEntry`).
def _parse_index_file(path):
    # File layout (big-endian); see
    # `src/plugins/ctf/common/lttng-index.hpp`.
    header_fmt = ">IIII"
    entry_fmt = ">QQQQQQQQQ"
    header_size = struct.calcsize(header_fmt)
    entry_size = struct.calcsize(entry_fmt)

    # Consume the whole file: LTTng index files are small (header,
    # fixed-size entries).
    data = path.read_bytes()

    # Decode and validate the header.
    #
    # The on-disk `packet_index_len` is what the file claims an entry
    # occupies; we expect it to match our structure.
    assert len(data) >= header_size, f"index file too small ({len(data)} bytes)"
    header = _IdxHeader(*struct.unpack(header_fmt, data[:header_size]))
    assert header.entry_size == entry_size, "unexpected on-disk entry size"

    # Walk the body one entry at a time, stepping by the on-disk entry
    # size (which equals our `entry_size` per the assertion above).
    body = data[header_size:]
    assert len(body) % header.entry_size == 0, "index body not a multiple of entry size"
    return header, [
        _IdxEntry(*struct.unpack(entry_fmt, body[i : i + entry_size]))
        for i in range(0, len(body), header.entry_size)
    ]


class _Iter(bt2._UserMessageIterator):
    def __init__(self, config, port):
        tc, sc, ec, opts = port.user_data
        environment = (
            {"tracer_name": opts.tracer_name} if opts.tracer_name is not None else None
        )
        stream = tc(environment=environment).create_stream(sc, name="the-stream")
        msgs = [self._create_stream_beginning_message(stream)]

        if opts.with_packets:
            for _ in range(opts.num_packets):
                pkt = stream.create_packet()
                msgs.append(self._create_packet_beginning_message(pkt))

                for _ in range(opts.events_per_pkt):
                    msgs.append(self._create_event_message(ec, pkt))

                msgs.append(self._create_packet_end_message(pkt))
        else:
            for _ in range(opts.events_per_pkt):
                msgs.append(self._create_event_message(ec, stream))

        msgs.append(self._create_stream_end_message(stream))
        self._msgs = msgs

    def __next__(self):
        if not self._msgs:
            raise StopIteration

        return self._msgs.pop(0)


# Test source component class.
#
# `obj` (in __init__()) is an object with the following attributes:
#
# `with_packets` (bool):
#     If true, then the stream class supports packets and the iterator
#     emits `num_packets` (see below) explicit packets.
#
#     Otherwise, the stream class doesn't support packets and the
#     component ignores `num_packets`.
#
# `num_packets` (integer):
#     Number of explicit packets the iterator emits (only when
#     `with_packets` above is true).
#
# `events_per_pkt` (integer):
#     Number of events the iterator emits per packet (or, when
#     `with_packets` above is false, per stream).
#
# `tracer_name` (string or `None`):
#     Value of the `tracer_name` trace environment entry.
#
#     If `None`, then the entry is omitted (the trace is not identified
#     as LTTng).
class _Src(bt2._UserSourceComponent, message_iterator_class=_Iter):
    def __init__(self, config, params, obj):
        tc = self._create_trace_class()

        if obj.with_packets:
            sc = tc.create_stream_class(supports_packets=True)
        else:
            sc = tc.create_stream_class()

        ec = sc.create_event_class(name="the-event")
        self._add_output_port("out", user_data=(tc, sc, ec, obj))

    @staticmethod
    def _user_get_supported_mip_versions(params, obj, log_level):
        return [0, 1]


# Runs a `_Src` component → `sink.ctf.fs` component conversion, writing
# the produced CTF trace to `trace_dir`.
#
# `obj` is forwarded as the `_Src` component initialization object (see
# above for its expected attributes).
#
# `ctf_version` is the value of the `ctf-version` parameter
# of `sink.ctf.fs`.
#
# `mode` is the value of the `create-lttng-index` parameter (`auto`,
# `always`, or `never`).
def _convert(sink_ctf_comp_cls, trace_dir, obj, ctf_version, mode):
    btu.convert(
        bt2.ComponentSpec(_Src, obj=obj),
        btu.SinkComponentSpec(
            sink_ctf_comp_cls,
            {
                "path": str(trace_dir),
                "assume-single-trace": True,
                "quiet": True,
                "ctf-version": ctf_version,
                "create-lttng-index": mode,
            },
        ),
    )


@pytest.fixture(scope="module", params=["1.8", "2"])
def trace_with_packets(request, sink_ctf_comp_cls, tmp_path_factory):
    ctf_version = request.param
    trace_dir = tmp_path_factory.mktemp(f"with-packets-ctf-{ctf_version}") / "the-trace"

    _convert(
        sink_ctf_comp_cls,
        trace_dir,
        types.SimpleNamespace(
            with_packets=True, num_packets=3, events_per_pkt=2, tracer_name=None
        ),
        ctf_version,
        "always",
    )

    return trace_dir


def test_with_packets_layout(trace_with_packets):
    assert (trace_with_packets / "metadata").is_file()
    assert (trace_with_packets / "the-stream").is_file()
    assert (trace_with_packets / "index/the-stream.idx").is_file()


def test_with_packets_header(trace_with_packets):
    header, _ = _parse_index_file(trace_with_packets / "index/the-stream.idx")
    assert header.magic == _LTTNG_IDX_MAGIC
    assert header.major == 1
    assert header.minor == 1


def test_with_packets_entry_count(trace_with_packets):
    _, entries = _parse_index_file(trace_with_packets / "index/the-stream.idx")
    assert len(entries) == 3


# Verifies that LTTng index entries describe contiguous, well-formed
# packets whose total covers the entire data stream file.
def test_with_packets_entries_are_consistent(trace_with_packets):
    stream_size = (trace_with_packets / "the-stream").stat().st_size
    _, entries = _parse_index_file(trace_with_packets / "index/the-stream.idx")
    expected_offset = 0
    total_packet_bytes = 0

    for i, entry in enumerate(entries):
        assert entry.offset == expected_offset, f"entry {i}: non-contiguous offset"
        assert entry.content_size <= entry.packet_size
        assert entry.packet_size % 8 == 0
        assert entry.packet_seq_num == i
        assert entry.stream_instance_id == entries[0].stream_instance_id
        assert entry.events_discarded == 0

        # All entries belong to the same stream
        assert entry.stream_id == entries[0].stream_id

        # Prepare for next entry
        packet_size_bytes = entry.packet_size // 8
        expected_offset += packet_size_bytes
        total_packet_bytes += packet_size_bytes

    assert total_packet_bytes == stream_size


def test_with_packets_round_trip(trace_with_packets):
    events = btu.tcmi_events(str(trace_with_packets))
    assert len(events) == 6
    assert all(ev.name == "the-event" for ev in events)


# Builds a CTF trace from a stream class that doesn't support packets
# (the `sink.ctf.fs` component synthesizes a single packet covering the
# whole stream).
@pytest.fixture(scope="module", params=["1.8", "2"])
def trace_without_packets(request, sink_ctf_comp_cls, tmp_path_factory):
    ctf_version = request.param
    trace_dir = tmp_path_factory.mktemp(f"no-packets-ctf-{ctf_version}") / "the-trace"

    _convert(
        sink_ctf_comp_cls,
        trace_dir,
        types.SimpleNamespace(
            with_packets=False, num_packets=0, events_per_pkt=3, tracer_name=None
        ),
        ctf_version,
        "always",
    )

    return trace_dir


def test_without_packets_index_exists(trace_without_packets):
    assert (trace_without_packets / "index/the-stream.idx").is_file()


# A stream without packet support yields exactly one synthetic LTTng
# index entry that spans the full data stream file.
def test_without_packets_index_has_one_entry(trace_without_packets):
    header, entries = _parse_index_file(trace_without_packets / "index/the-stream.idx")
    assert header.magic == _LTTNG_IDX_MAGIC
    assert len(entries) == 1
    entry = entries[0]
    assert entry.offset == 0
    assert entry.packet_seq_num == 0
    stream_size = (trace_without_packets / "the-stream").stat().st_size
    assert entry.packet_size == stream_size * 8


def test_without_packets_round_trip(trace_without_packets):
    events = btu.tcmi_events(str(trace_without_packets))
    assert len(events) == 3


# Verifies that `src.ctf.fs` still reads a trace whose `.idx` file has
# been corrupted, falling back to scanning the stream file directly.
#
# This guards against round-trip-only assertions silently masking a
# broken index.
@pytest.mark.parametrize("ctf_version", ["1.8", "2"])
def test_corrupt_index_falls_back_to_stream_scan(
    ctf_version, sink_ctf_comp_cls, tmp_path_factory
):
    trace_dir = tmp_path_factory.mktemp(f"corrupt-ctf-{ctf_version}") / "the-trace"

    _convert(
        sink_ctf_comp_cls,
        trace_dir,
        types.SimpleNamespace(
            with_packets=True, num_packets=2, events_per_pkt=1, tracer_name=None
        ),
        ctf_version,
        "always",
    )

    # Open LTTng index file
    idx_path = trace_dir / "index/the-stream.idx"
    data = bytearray(idx_path.read_bytes())

    # Clobber magic
    data[0] ^= 0xFF

    # Write back corrupted LTTng index file
    idx_path.write_bytes(bytes(data))

    # Verify
    events = btu.tcmi_events(str(trace_dir))
    assert len(events) == 2


# With `create-lttng-index=never`, the component doesn't write an LTTng
# index, even when the trace is identified as LTTng.
def test_never_no_index(sink_ctf_comp_cls, tmp_path_factory):
    trace_dir = tmp_path_factory.mktemp("never") / "the-trace"

    _convert(
        sink_ctf_comp_cls,
        trace_dir,
        types.SimpleNamespace(
            with_packets=True,
            num_packets=1,
            events_per_pkt=1,
            tracer_name="lttng-ust",
        ),
        "2",
        "never",
    )

    assert not (trace_dir / "index").exists()


# With `create-lttng-index=auto` (the default): write the index if and
# only if the `tracer_name` environment entry of the `trace` identifies
# it as an LTTng trace.
@pytest.mark.parametrize(
    ["tracer_name", "expect_index"],
    [
        pytest.param("lttng-ust", True, id="lttng-ust"),
        pytest.param("lttng-modules", True, id="lttng-modules"),
        pytest.param("other-tracer", False, id="other-tracer"),
        pytest.param(None, False, id="no-tracer-name"),
    ],
)
def test_auto(sink_ctf_comp_cls, tmp_path_factory, tracer_name, expect_index):
    trace_dir = (
        tmp_path_factory.mktemp(f"auto-{tracer_name or 'no-name'}") / "the-trace"
    )

    _convert(
        sink_ctf_comp_cls,
        trace_dir,
        types.SimpleNamespace(
            with_packets=True,
            num_packets=1,
            events_per_pkt=1,
            tracer_name=tracer_name,
        ),
        "2",
        "auto",
    )

    assert (trace_dir / "index/the-stream.idx").is_file() == expect_index

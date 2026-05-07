# SPDX-FileCopyrightText: 2026 EfficiOS Inc.
# SPDX-License-Identifier: GPL-2.0-only

import bt2
import pytest
import bt_tests_utils as btu


class _Iter(bt2._UserMessageIterator):
    def __init__(self, config, port):
        tc, sc, ec, tracer_name = port.user_data
        environment = {"tracer_name": tracer_name} if tracer_name is not None else None
        stream = tc(environment=environment).create_stream(sc, name="the-stream")
        pkt = stream.create_packet()
        pkt.context_field["cpu_id"] = 0

        self._msgs = [
            self._create_stream_beginning_message(stream),
            self._create_packet_beginning_message(pkt),
            self._create_event_message(ec, pkt),
            self._create_packet_end_message(pkt),
            self._create_stream_end_message(stream),
        ]

    def __next__(self):
        if not self._msgs:
            raise StopIteration

        return self._msgs.pop(0)


# Test source component class.
#
# The message iterator emits a single packet, with a context field,
# containing one event. The packet context field has a single `cpu_id`
# member (unsigned integer field).
#
# The initialization object (`obj`) is a string or `None` controlling
# the value of the `tracer_name` trace environment entry (when not
# `None`).
#
# Used by the tests below to verify how a `sink.ctf.fs` component writes
# the `cpu_id` packet context member name in the resulting CTF 1.8
# metadata stream.
class _Src(bt2._UserSourceComponent, message_iterator_class=_Iter):
    def __init__(self, config, params, obj):
        tc = self._create_trace_class()
        sc = tc.create_stream_class(
            supports_packets=True,
            packet_context_field_class=tc.create_structure_field_class(
                members=[("cpu_id", tc.create_unsigned_integer_field_class())]
            ),
        )
        ec = sc.create_event_class(name="the-event")
        self._add_output_port("out", user_data=(tc, sc, ec, obj))

    @staticmethod
    def _user_get_supported_mip_versions(params, obj, log_level):
        return [0, 1]


# Verifies how the `cpu_id` packet context member name appears in the
# metadata stream file under five configurations.
@pytest.mark.parametrize(
    ["ctf_version", "mode", "tracer_name", "expected_present", "expected_absent"],
    [
        # CTF 1.8 + `create-lttng-index=always`: the Trace Compass
        # workaround is active and the name is unescaped (`cpu_id`).
        pytest.param(
            "1.8",
            "always",
            None,
            b" cpu_id;",
            b"_cpu_id",
            id="ctf-1.8-always-unescaped",
        ),
        # CTF 1.8 + `create-lttng-index=never`: systematic TSDL member
        # name escaping (`_cpu_id`).
        pytest.param(
            "1.8",
            "never",
            None,
            b" _cpu_id;",
            b" cpu_id;",
            id="ctf-1.8-never-escaped",
        ),
        # CTF 1.8 + `create-lttng-index=auto` + LTTng trace: the Trace
        # Compass workaround is active and the name is
        # unescaped (`cpu_id`).
        pytest.param(
            "1.8",
            "auto",
            "lttng-ust",
            b" cpu_id;",
            b"_cpu_id",
            id="ctf-1.8-auto-lttng-unescaped",
        ),
        # CTF 1.8 + `create-lttng-index=auto` + non-LTTng trace:
        # systematic TSDL member name escaping (`_cpu_id`).
        pytest.param(
            "1.8",
            "auto",
            None,
            b" _cpu_id;",
            b" cpu_id;",
            id="ctf-1.8-auto-non-lttng-escaped",
        ),
        # CTF 2 + `create-lttng-index=always`: doesn't apply (no TSDL
        # escaping in CTF 2; the name is left as `cpu_id`).
        pytest.param(
            "2",
            "always",
            None,
            b'"cpu_id"',
            b"_cpu_id",
            id="ctf-2-no-escape",
        ),
    ],
)
def test_cpu_id_in_metadata(
    sink_ctf_comp_cls,
    tmp_path_factory,
    ctf_version,
    mode,
    tracer_name,
    expected_present,
    expected_absent,
):
    trace_dir = tmp_path_factory.mktemp("tc-workaround") / "the-trace"

    btu.convert(
        bt2.ComponentSpec(_Src, obj=tracer_name),
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

    metadata = (trace_dir / "metadata").read_bytes()
    assert expected_present in metadata
    assert expected_absent not in metadata

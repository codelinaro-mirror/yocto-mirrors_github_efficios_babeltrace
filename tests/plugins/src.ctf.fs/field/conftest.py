# SPDX-FileCopyrightText: 2023-2025 Efficios, Inc.
# SPDX-License-Identifier: GPL-2.0-only

# pyright: strict, reportMissingTypeStubs=false, reportPrivateUsage=false

import string
import typing
import logging
import pathlib
import tempfile
from typing import Any, List, Tuple, Union, Optional

import bt2
import pytest
import normand
import moultipart
import bt_tests_utils as btu

logger = logging.getLogger(__name__)
_ARRAY_ELEM = object()


# Recursively converts `field` to a string with the indentation level
# `indent` and the introduction `intro`.
#
# `intro` is one of:
#
# `None`:
#     No introduction (root field).
#
# A string:
#     Structure field member name.
#
# `_ARRAY_ELEM`:
#     `field` is an array field element.
def _field_to_str(
    intro: Union[None, str, object], field: bt2._FieldConst, indent: int = 0
) -> str:
    indent_str = " " * indent * 2
    intro_str = ""

    if intro is _ARRAY_ELEM:
        intro_str = "- "
    elif intro is not None:
        intro_str = f"{intro}: "

    if isinstance(field, bt2._StringFieldConst):
        return f'{indent_str}{intro_str}"{field}"'
    elif isinstance(field, bt2._StructureFieldConst):
        if len(field) == 0:
            # Special case for an empty structure field
            return f"{indent_str}{intro_str}∅"
        else:
            if intro is _ARRAY_ELEM:
                # Structure field is an array field element itself:
                # format the first element first, and then format the
                # remaining ones indented.
                sub_field_names = typing.cast(List[str], list(field))
                lines = [
                    f"{indent_str}{intro_str}{_field_to_str(sub_field_names[0], field[sub_field_names[0]], 0)}"
                ]

                for sub_field_name in sub_field_names[1:]:
                    lines.append(
                        _field_to_str(sub_field_name, field[sub_field_name], indent + 1)
                    )

                return "\n".join(lines)
            else:
                lines: List[str] = []

                if intro is not None:
                    # Structure field has a name: format it and a
                    # newline, and then format all the members indented
                    # (one more level).
                    lines.append(f"{indent_str}{intro}:")
                    indent += 1

                for sub_field_name in field:
                    lines.append(
                        _field_to_str(sub_field_name, field[sub_field_name], indent)
                    )

                return "\n".join(lines)
    elif isinstance(field, bt2._ArrayFieldConst):
        if len(field) == 0:
            # Special case for an empty array field
            return f"{indent_str}{intro_str}∅"

        lines: List[str] = []

        if intro is not None:
            # Array field has an intro: format it, then format a newline,
            # and then format all the elements indented (one more level).
            lines.append(f"{indent_str}{intro_str.rstrip()}")
            indent += 1

        for sub_field in typing.cast(List[bt2._FieldConst], field):
            lines.append(_field_to_str(_ARRAY_ELEM, sub_field, indent))

        return "\n".join(lines)
    elif isinstance(field.cls, bt2._IntegerFieldClassConst):
        # Honor the preferred display base
        base = field.cls.preferred_display_base
        int_val = int(typing.cast(Any, field))

        if base == 10:
            return f"{indent_str}{intro_str}{int_val}"
        elif base == 16:
            return f"{indent_str}{intro_str}{hex(int_val)}"
        elif base == 8:
            return f"{indent_str}{intro_str}{oct(int_val)}"
        else:
            assert base == 2
            return f"{indent_str}{intro_str}{bin(int_val)}"
    elif isinstance(field, bt2._BitArrayFieldConst):
        bits = ", ".join(
            str((field.value_as_integer >> i) & 1)
            for i in range(field.cls.length - 1, -1, -1)
        )
        return f"{indent_str}{intro_str}[{bits}]"
    elif isinstance(field, bt2._BlobFieldConst):
        if len(field) == 0:
            return f"{indent_str}{intro_str}∅"

        bytes_str = " ".join(f"{b:02x}" for b in field.data)
        return f"{indent_str}{intro_str}{bytes_str}"
    elif isinstance(field, bt2._BoolFieldConst):
        return f"{indent_str}{intro_str}{'yes' if field else 'no'}"
    elif isinstance(field, bt2._RealFieldConst):
        return f"{indent_str}{intro_str}{float(field):.6f}"
    elif isinstance(field, bt2._OptionFieldConst):
        if field.has_field:
            return _field_to_str(
                intro, typing.cast(bt2._FieldConst, field.field), indent
            )
        else:
            # Special case for an option field without a field
            return f"{indent_str}{intro_str}~"
    elif isinstance(field, bt2._VariantFieldConst):
        return _field_to_str(intro, field.selected_option, indent)
    else:
        return f"{indent_str}{intro_str}{field}"


def _make_ctf_1_metadata(payload_fc: str) -> str:
    if "@" in payload_fc:
        payload_fc = payload_fc.replace("@", "root")
    else:
        payload_fc += " root"

    return string.Template("""
/* CTF 1.8 */

trace {
    major = 1;
    minor = 8;
    byte_order = le;
};

typealias integer { size = 8; } := u8;
typealias integer { size = 16; } := u16;
typealias integer { size = 32; } := u32;
typealias integer { size = 64; } := u64;
typealias integer { size = 8; byte_order = le; } := u8le;
typealias integer { size = 16; byte_order = le; } := u16le;
typealias integer { size = 32; byte_order = le; } := u32le;
typealias integer { size = 64; byte_order = le; } := u64le;
typealias integer { size = 8; byte_order = be; } := u8be;
typealias integer { size = 16; byte_order = be; } := u16be;
typealias integer { size = 32; byte_order = be; } := u32be;
typealias integer { size = 64; byte_order = be; } := u64be;
typealias integer { signed = true; size = 8; } := i8;
typealias integer { signed = true; size = 16; } := i16;
typealias integer { signed = true; size = 32; } := i32;
typealias integer { signed = true; size = 64; } := i64;
typealias integer { signed = true; size = 8; byte_order = le; } := i8le;
typealias integer { signed = true; size = 16; byte_order = le; } := i16le;
typealias integer { signed = true; size = 32; byte_order = le; } := i32le;
typealias integer { signed = true; size = 64; byte_order = le; } := i64le;
typealias integer { signed = true; size = 8; byte_order = be; } := i8be;
typealias integer { signed = true; size = 16; byte_order = be; } := i16be;
typealias integer { signed = true; size = 32; byte_order = be; } := i32be;
typealias integer { signed = true; size = 64; byte_order = be; } := i64be;
typealias floating_point { exp_dig = 8; mant_dig = 24; } := flt32;
typealias floating_point { exp_dig = 11; mant_dig = 53; } := flt64;
typealias floating_point { exp_dig = 8; mant_dig = 24; byte_order = le; } := flt32le;
typealias floating_point { exp_dig = 11; mant_dig = 53; byte_order = le; } := flt64le;
typealias floating_point { exp_dig = 8; mant_dig = 24; byte_order = be; } := flt32be;
typealias floating_point { exp_dig = 11; mant_dig = 53; byte_order = be; } := flt64be;
typealias string { encoding = UTF8; } := nt_str;

event {
    name = the_event;
    fields := struct {
        ${payload_fc};
    };
};
""").substitute(payload_fc=payload_fc).rstrip()


def _make_ctf_2_metadata(payload_fc: str) -> str:
    return string.Template("""
\x1e{
  "type": "preamble",
  "version": 2
}
\x1e{
  "type": "field-class-alias",
  "name": "u8le",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 8,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u16le",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 16,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u32le",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 32,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u64le",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 64,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u8",
  "field-class": "u8le"
}
\x1e{
  "type": "field-class-alias",
  "name": "u16",
  "field-class": "u16le"
}
\x1e{
  "type": "field-class-alias",
  "name": "u32",
  "field-class": "u32le"
}
\x1e{
  "type": "field-class-alias",
  "name": "u64",
  "field-class": "u64le"
}
\x1e{
  "type": "field-class-alias",
  "name": "u8be",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 8,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u16be",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 16,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u32be",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 32,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "u64be",
  "field-class": {
    "type": "fixed-length-unsigned-integer",
    "length": 64,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i8le",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 8,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i16le",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 16,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i32le",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 32,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i64le",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 64,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i8be",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 8,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i16be",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 16,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i32be",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 32,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i64be",
  "field-class": {
    "type": "fixed-length-signed-integer",
    "length": 64,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "i8",
  "field-class": "i8le"
}
\x1e{
  "type": "field-class-alias",
  "name": "i16",
  "field-class": "i16le"
}
\x1e{
  "type": "field-class-alias",
  "name": "i32",
  "field-class": "i32le"
}
\x1e{
  "type": "field-class-alias",
  "name": "i64",
  "field-class": "i64le"
}
\x1e{
  "type": "field-class-alias",
  "name": "flt32le",
  "field-class": {
    "type": "fixed-length-floating-point-number",
    "length": 32,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "flt64le",
  "field-class": {
    "type": "fixed-length-floating-point-number",
    "length": 64,
    "byte-order": "little-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "flt32",
  "field-class": "flt32le"
}
\x1e{
  "type": "field-class-alias",
  "name": "flt64",
  "field-class": "flt64le"
}
\x1e{
  "type": "field-class-alias",
  "name": "flt32be",
  "field-class": {
    "type": "fixed-length-floating-point-number",
    "length": 32,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "flt64be",
  "field-class": {
    "type": "fixed-length-floating-point-number",
    "length": 64,
    "byte-order": "big-endian",
    "alignment": 8
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "nt-str-utf-8",
  "field-class": {
    "type": "null-terminated-string"
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "nt-str-utf-16be",
  "field-class": {
    "type": "null-terminated-string",
    "encoding": "utf-16be"
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "nt-str-utf-16le",
  "field-class": {
    "type": "null-terminated-string",
    "encoding": "utf-16le"
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "nt-str-utf-32be",
  "field-class": {
    "type": "null-terminated-string",
    "encoding": "utf-32be"
  }
}
\x1e{
  "type": "field-class-alias",
  "name": "nt-str-utf-32le",
  "field-class": {
    "type": "null-terminated-string",
    "encoding": "utf-32le"
  }
}
\x1e{
  "type": "data-stream-class"
}
\x1e{
  "type": "event-record-class",
  "payload-field-class": {
    "type": "structure",
    "member-classes": [
      {
        "name": "root",
        "field-class": ${payload_fc}
      }
    ]
  }
}
""").substitute(payload_fc=payload_fc).lstrip("\n").rstrip()


def _make_ctf_metadata(payload_fc: str) -> str:
    if payload_fc.startswith("{") or payload_fc.startswith('"'):
        # CTF 2
        return _make_ctf_2_metadata(payload_fc)
    else:
        # Assume CTF 1.8
        return _make_ctf_1_metadata(payload_fc)


def _make_ctf_data(normand_text: str) -> bytearray:
    # Default to little-endian because that's also the default in
    # _make_ctf_1_metadata() and _make_ctf_2_metadata() above.
    return normand.parse(f"!le\n{normand_text}").data


class _FieldTestItem(pytest.Item):
    def __init__(self, *, mp_path: pathlib.Path, **kwargs: Any) -> None:
        super().__init__(**kwargs)  # pyright: ignore[reportUnknownMemberType]
        self._mp_path = mp_path

    def runtest(self) -> None:
        # Parse the moultipart file
        with open(self._mp_path, "r", encoding="utf-8") as f:
            parts = moultipart.parse(f)

        # Create temporary directory for trace
        with tempfile.TemporaryDirectory() as tmp_dir:
            trace_dir = pathlib.Path(tmp_dir) / "trace"
            trace_dir.mkdir()

            # Write metadata stream
            metadata_path = trace_dir / "metadata"
            metadata_path.write_text(
                _make_ctf_metadata(parts[0].content.strip()), encoding="utf-8"
            )

            # Write data stream
            data_path = trace_dir / "data"
            data_path.write_bytes(_make_ctf_data(parts[1].content))

            # Expected output
            expected = parts[2].content

            # Run the trace through btu.tcmi_events() and build
            # actual output (single event).
            events = btu.tcmi_events(str(trace_dir))
            assert len(events) == 1
            payload = events[0].payload_field
            assert "root" in payload
            assert len(payload) == 1
            actual = f"{_field_to_str(None, payload['root'])}\n"

            if actual.strip() != expected.strip():
                raise _FieldTestException(self._mp_path, expected, actual)

    def reportinfo(self) -> Tuple[Any, None, str]:
        return self.path, None, self.name

    def repr_failure(
        self,
        excinfo: "pytest.ExceptionInfo[BaseException]",
        style: Any = None,
    ) -> Any:
        if isinstance(excinfo.value, _FieldTestException):
            return excinfo.value.format_output()

        return super().repr_failure(excinfo, style)


class _FieldTestException(Exception):
    def __init__(self, mp_path: pathlib.Path, expected: str, actual: str) -> None:
        super().__init__(f"Field test failed for `{mp_path}`")
        self._mp_path = mp_path
        self._expected = expected
        self._actual = actual

    def format_output(self) -> str:
        return "\n".join(
            [
                f"📄 Test file: `{self._mp_path}`",
                "",
                "✅ Expected:",
                self._expected,
                "",
                "❌ Actual:",
                self._actual,
            ]
        )


class _FieldTestFile(pytest.File):
    def collect(self) -> List[_FieldTestItem]:
        logger.info(f"Adding field test from `{self.path}`")

        item = _FieldTestItem.from_parent(  # pyright: ignore[reportUnknownMemberType]
            name="test",
            parent=self,
            mp_path=self.path,
        )
        return [item]


# pytest hook.
def pytest_collect_file(
    file_path: pathlib.Path, parent: pytest.Collector
) -> Optional[_FieldTestFile]:
    if file_path.suffix == ".mp" and (
        file_path.name.startswith("ctf-2-pass-")
        or file_path.name.startswith("ctf-1.8-pass-")
    ):
        return _FieldTestFile.from_parent(  # pyright: ignore[reportUnknownMemberType]
            parent=parent, path=file_path
        )

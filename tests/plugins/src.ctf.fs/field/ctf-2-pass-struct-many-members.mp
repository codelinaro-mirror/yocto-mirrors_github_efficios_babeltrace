---
{
  "type": "structure",
  "member-classes": [
    {"name": "m01", "field-class": "u8"},
    {"name": "m02", "field-class": "i16le"},
    {"name": "m03", "field-class": "u32le"},
    {"name": "m04", "field-class": "i64le"},
    {"name": "m05", "field-class": "flt32le"},
    {"name": "m06", "field-class": "flt64le"},
    {"name": "m07", "field-class": "nt-str-utf-8"},
    {"name": "m08", "field-class": "u8"},
    {"name": "m09", "field-class": "i16le"},
    {"name": "m10", "field-class": "u32le"}
  ]
}

---
$1            # `m01`
[-2:16le]     # `m02`
[3:32le]      # `m03`
[-4:64le]     # `m04`
[5.5:32le]    # `m05`
[6.25:64le]   # `m06`
"hello\0"     # `m07`
$8            # `m08`
[-9:16le]     # `m09`
[10:32le]     # `m10`

---
m01: 1
m02: -2
m03: 3
m04: -4
m05: 5.500000
m06: 6.250000
m07: "hello"
m08: 8
m09: -9
m10: 10

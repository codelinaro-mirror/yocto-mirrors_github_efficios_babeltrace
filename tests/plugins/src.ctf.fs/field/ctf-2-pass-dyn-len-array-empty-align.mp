---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {"name": "before", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len"]},
        "element-field-class": {
          "type": "fixed-length-unsigned-integer",
          "length": 32,
          "byte-order": "little-endian",
          "alignment": 32
        }
      }
    },
    {"name": "after", "field-class": "nt-str-utf-8"}
  ]
}

---
$0            # `len`
$42           # `before`
@32           # 16 bits of padding
"hello!" 00   # `after`

---
len: 0
before: 42
arr: ∅
after: "hello!"

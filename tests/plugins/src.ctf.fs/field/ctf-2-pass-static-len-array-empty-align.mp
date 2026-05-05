---
{
  "type": "structure",
  "member-classes": [
    {"name": "before", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "static-length-array",
        "length": 0,
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
$42           # `before`
@32           # 24 bits of padding
"hello!" 00   # `after`

---
before: 42
arr: ∅
after: "hello!"

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
        "minimum-alignment": 32,
        "element-field-class": "u8"
      }
    },
    {"name": "after", "field-class": "nt-str-utf-8"}
  ]
}

---
$3            # `len`
$42           # `before`
@32           # 16 bits of padding
$10 $20 $30   # `arr`
"hello!" 00   # `after`

---
len: 3
before: 42
arr:
  - 10
  - 20
  - 30
after: "hello!"

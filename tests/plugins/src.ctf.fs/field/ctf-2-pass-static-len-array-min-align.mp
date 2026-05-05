---
{
  "type": "structure",
  "member-classes": [
    {"name": "before", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "static-length-array",
        "length": 3,
        "minimum-alignment": 32,
        "element-field-class": "u8"
      }
    },
    {"name": "after", "field-class": "nt-str-utf-8"}
  ]
}

---
$42           # `before`
@32           # 24 bits of padding
$10 $20 $30   # `arr`
"hello!" 00   # `after`

---
before: 42
arr:
  - 10
  - 20
  - 30
after: "hello!"

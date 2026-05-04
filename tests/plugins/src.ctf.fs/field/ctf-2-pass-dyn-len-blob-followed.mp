---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "before",
      "field-class": {
        "type": "dynamic-length-blob",
        "length-field-location": {
          "path": ["len"]
        }
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
$4            # `len`
01 02 03 04   # `before`
$42           # `after`

---
len: 4
before: 01 02 03 04
after: 42

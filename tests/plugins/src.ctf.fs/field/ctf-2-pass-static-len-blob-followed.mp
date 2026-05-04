---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "before",
      "field-class": {
        "type": "static-length-blob",
        "length": 4
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
01 02 03 04   # `before`
$42           # `after`

---
before: 01 02 03 04
after: 42

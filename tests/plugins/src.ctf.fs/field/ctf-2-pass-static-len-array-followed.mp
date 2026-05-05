---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "arr",
      "field-class": {
        "type": "static-length-array",
        "length": 3,
        "element-field-class": "u16le"
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
[100:16le] [200:16le] [300:16le]  # `arr`
$42                               # `tail`

---
arr:
  - 100
  - 200
  - 300
tail: 42

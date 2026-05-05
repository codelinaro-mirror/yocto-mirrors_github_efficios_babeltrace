---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len"]},
        "element-field-class": "u16le"
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
$3                                # `len`
[100:16le] [200:16le] [300:16le]  # `arr`
$42                               # `tail`

---
len: 3
arr:
  - 100
  - 200
  - 300
tail: 42

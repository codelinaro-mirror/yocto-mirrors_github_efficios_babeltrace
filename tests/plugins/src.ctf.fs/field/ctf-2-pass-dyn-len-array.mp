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
        "element-field-class": "u8"
      }
    }
  ]
}

---
$4            # `len`
01 02 03 04   # `arr`

---
len: 4
arr:
  - 1
  - 2
  - 3
  - 4

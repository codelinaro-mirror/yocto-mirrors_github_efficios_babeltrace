---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "len",
      "field-class": {"type": "variable-length-unsigned-integer"}
    },
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len"]},
        "element-field-class": "u16le"
      }
    }
  ]
}

---
[3:uleb128]               # `len`
[10:16] [20:16] [30:16]   # `arr`

---
len: 3
arr:
  - 10
  - 20
  - 30

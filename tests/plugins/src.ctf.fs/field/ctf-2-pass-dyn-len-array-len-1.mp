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
$1    # `len`
$42   # `arr`

---
len: 1
arr:
  - 42

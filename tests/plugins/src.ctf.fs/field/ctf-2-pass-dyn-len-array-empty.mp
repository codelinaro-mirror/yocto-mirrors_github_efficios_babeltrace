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
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
$0    # `len`
$42   # `tail`

---
len: 0
arr: ∅
tail: 42

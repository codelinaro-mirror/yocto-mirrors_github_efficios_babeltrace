---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "blob",
      "field-class": {
        "type": "dynamic-length-blob",
        "length-field-location": {
          "path": ["len"]
        }
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
blob: ∅
tail: 42

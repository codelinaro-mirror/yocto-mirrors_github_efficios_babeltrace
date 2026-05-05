---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "len",
      "field-class": {"type": "variable-length-unsigned-integer"}
    },
    {
      "name": "blob",
      "field-class": {
        "type": "dynamic-length-blob",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
[5:uleb128]     # `len`
aa bb cc dd ee  # `blob`

---
len: 5
blob: aa bb cc dd ee

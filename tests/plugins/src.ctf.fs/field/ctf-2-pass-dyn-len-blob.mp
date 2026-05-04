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
    }
  ]
}

---
$5              # `len`
aa bb cc dd ee  # `blob`

---
len: 5
blob: aa bb cc dd ee

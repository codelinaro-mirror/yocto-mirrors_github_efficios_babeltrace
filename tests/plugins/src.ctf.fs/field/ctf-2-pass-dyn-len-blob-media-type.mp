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
        },
        "media-type": "image/png"
      }
    }
  ]
}

---
$8                        # `len`
89 50 4e 47 0d 0a 1a 0a   # `blob`

---
len: 8
blob: 89 50 4e 47 0d 0a 1a 0a

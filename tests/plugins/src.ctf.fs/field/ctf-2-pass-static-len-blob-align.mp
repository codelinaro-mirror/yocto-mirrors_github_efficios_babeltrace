---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "pad",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "blob",
      "field-class": {
        "type": "static-length-blob",
        "length": 5
      }
    }
  ]
}

---
[5:8le]         # `pad` (low nibble) + 4 bits of padding
aa bb cc dd ee  # `blob`

---
pad: 5
blob: aa bb cc dd ee

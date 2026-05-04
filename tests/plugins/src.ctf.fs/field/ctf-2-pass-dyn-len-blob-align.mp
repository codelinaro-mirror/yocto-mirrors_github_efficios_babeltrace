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
    {"name": "len", "field-class": "u8"},
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
[5:8le]         # `pad` (low nibble) + 4 bits of padding
$5              # `len`
aa bb cc dd ee  # `blob`

---
pad: 5
len: 5
blob: aa bb cc dd ee

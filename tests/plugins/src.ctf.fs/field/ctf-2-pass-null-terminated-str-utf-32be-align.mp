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
    {"name": "str", "field-class": "nt-str-utf-32be"}
  ]
}

---
[5:8le]                            # `pad` (low nibble) + 4 bits of padding
u32be"café 日本語 🎉" 00 00 00 00   # `str`

---
pad: 5
str: "café 日本語 🎉"

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
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-8",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
[5:8le]          # `pad` (low nibble) + 4 bits of padding
$20              # `len`
"café 日本語 🎉"  # `str`

---
pad: 5
len: 20
str: "café 日本語 🎉"

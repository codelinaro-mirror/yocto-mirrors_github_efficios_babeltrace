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
      "name": "arr",
      "field-class": {
        "type": "static-length-array",
        "length": 3,
        "minimum-alignment": 32,
        "element-field-class": "u32le"
      }
    }
  ]
}

---
[5:8le]                           # `pad` (low nibble) + 4 bits of padding
@32                               # 24 bits of padding
[100:32le] [200:32le] [300:32le]  # `arr`

---
pad: 5
arr:
  - 100
  - 200
  - 300

---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "u",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "s",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "pad",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 6,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
[(0 << 2) | (1 << 1) | 1 : 8]

---
u: 1
s: -1
pad: 0

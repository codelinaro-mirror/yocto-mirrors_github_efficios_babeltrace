---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 5,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "pad",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 3,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
[(0 << 5) | (-5 & 0x1f) : 8]

---
a: -5
pad: 0

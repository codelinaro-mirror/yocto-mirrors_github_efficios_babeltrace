---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 12,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 12,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
[((50 & 0xfff) << 12) | (-100 & 0xfff) : 24le]

---
a: -100
b: 50

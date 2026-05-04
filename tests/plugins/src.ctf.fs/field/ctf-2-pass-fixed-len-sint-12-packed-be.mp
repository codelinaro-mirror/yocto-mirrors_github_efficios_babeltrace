---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 12,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 12,
        "byte-order": "big-endian",
        "alignment": 1
      }
    }
  ]
}

---
[((-100 & 0xfff) << 12) | (50 & 0xfff) : 24be]

---
a: -100
b: 50

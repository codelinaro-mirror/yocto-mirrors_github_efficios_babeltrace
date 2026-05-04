---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "big-endian",
        "alignment": 1
      }
    }
  ]
}

---
[(3 << 4) | 12 : 8]

---
a: 3
b: 12

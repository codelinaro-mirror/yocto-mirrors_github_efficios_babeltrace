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
      "name": "f",
      "field-class": {
        "type": "fixed-length-floating-point-number",
        "length": 32,
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
# 1.5 is 0x3fc00000 (IEEE 754 binary32)
[(5 << 36) | (0x3fc00000 << 4) | 10 : 40be]

---
a: 5
f: 1.500000
b: 10

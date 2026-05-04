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
        "length": 64,
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
# `a`: 5
# `f`: 0.5 (0x3fe0000000000000 as IEEE 754 binary64)
# `b`: 10
53 fe 00 00 00 00 00 00 0a

---
a: 5
f: 0.500000
b: 10

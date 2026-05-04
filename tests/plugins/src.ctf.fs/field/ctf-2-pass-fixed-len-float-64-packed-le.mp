---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "f",
      "field-class": {
        "type": "fixed-length-floating-point-number",
        "length": 64,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
# `a`: 5
# `f`: 0.5 (0x3fe0000000000000 as IEEE 754 binary64)
# `b`: 10
05 00 00 00 00 00 00 fe a3

---
a: 5
f: 0.500000
b: 10

---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 5,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 10,
        "byte-order": "little-endian",
        "alignment": 2
      }
    }
  ]
}

---
% 10          # `b` (low 2 bits)
  0           # 1 bit of padding
  10110       # `a`
% 10101010    # `b` (high 8 bits)

---
a: [1, 0, 1, 1, 0]
b: [1, 0, 1, 0, 1, 0, 1, 0, 1, 0]

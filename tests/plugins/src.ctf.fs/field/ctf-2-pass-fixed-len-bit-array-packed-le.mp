---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
%
  1100  # `a`
  0011  # `b`

---
a: [0, 0, 1, 1]
b: [1, 1, 0, 0]

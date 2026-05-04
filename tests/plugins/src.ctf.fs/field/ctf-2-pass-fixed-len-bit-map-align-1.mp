---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 5,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 11,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    }
  ]
}

---
% 101         # `b` (low 3 bits)
  10110       # `a`
% 10101010    # `b` (high 8 bits)

---
a: [1, 0, 1, 1, 0]
b: [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]

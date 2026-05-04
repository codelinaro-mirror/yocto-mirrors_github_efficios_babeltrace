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
        "length": 8,
        "byte-order": "little-endian",
        "alignment": 4,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    }
  ]
}

---
%%
  000       # 3 bits of padding before `a`
  10110     # `a`(low 5 bits)
  11001100  # `b`

---
a: [1, 0, 1, 1, 0]
b: [1, 1, 0, 0, 1, 1, 0, 0]

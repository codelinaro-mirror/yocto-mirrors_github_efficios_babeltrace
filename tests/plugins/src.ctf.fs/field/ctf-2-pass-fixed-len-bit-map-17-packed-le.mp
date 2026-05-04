---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 3,
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
        "length": 17,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 4,
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
%%% 00000101 00110101 10011100

---
a: [1, 0, 1]
b: [1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0]
c: [1, 0, 0, 1]

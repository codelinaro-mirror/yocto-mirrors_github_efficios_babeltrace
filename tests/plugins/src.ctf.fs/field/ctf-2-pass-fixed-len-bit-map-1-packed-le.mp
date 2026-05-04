---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 1,
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
        "length": 1,
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
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "d",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "e",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "f",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "g",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1,
        "flags": {
          "flag": [[0, 0]]
        }
      }
    },
    {
      "name": "h",
      "field-class": {
        "type": "fixed-length-bit-map",
        "length": 1,
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
%
  0   # `h` (bit 7, MSB)
  1   # `g`
  0   # `f`
  0   # `e`
  1   # `d`
  1   # `c`
  0   # `b`
  1   # `a` (bit 0, LSB)

---
a: [1]
b: [0]
c: [1]
d: [1]
e: [0]
f: [0]
g: [1]
h: [0]

---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "d",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "e",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "f",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "g",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "h",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
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
a: yes
b: no
c: yes
d: yes
e: no
f: no
g: yes
h: no

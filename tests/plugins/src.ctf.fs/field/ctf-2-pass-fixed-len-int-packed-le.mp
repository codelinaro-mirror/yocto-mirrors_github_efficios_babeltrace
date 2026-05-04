---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 3,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 7,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 6,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "d",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 8,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
[((-1 & 0xff) << 16) | (42 << 10) | ((-10 & 0x7f) << 3) | 5:24le]

---
a: 5
b: -10
c: 42
d: -1

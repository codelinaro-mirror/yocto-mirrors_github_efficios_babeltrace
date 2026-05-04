---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 3,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 7,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 6,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "d",
      "field-class": {
        "type": "fixed-length-signed-integer",
        "length": 8,
        "byte-order": "big-endian",
        "alignment": 1
      }
    }
  ]
}

---
[(5 << 21) | ((-10 & 0x7f) << 14) | (42 << 8) | (-1 & 0xff) : 24be]

---
a: 5
b: -10
c: 42
d: -1

---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 3,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 17,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 4,
        "byte-order": "big-endian",
        "alignment": 1
      }
    }
  ]
}

---
%%% 10111000 01101010 00001001

---
a: [1, 0, 1]
b: [1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0]
c: [1, 0, 0, 1]

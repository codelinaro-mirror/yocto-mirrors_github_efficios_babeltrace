---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": "u8le"
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 32,
        "byte-order": "little-endian",
        "alignment": 32
      }
    }
  ]
}

---
%     00000001                              # `a`
%%%   00010010 00110100 01000101            # padding to 32-bit alignment for `b`
%%%%  11011101 11001100 10111011 10101010   # `b`

---
a: 1
b: [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1]

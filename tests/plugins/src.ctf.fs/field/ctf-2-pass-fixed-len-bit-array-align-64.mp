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
        "length": 64,
        "byte-order": "little-endian",
        "alignment": 64
      }
    }
  ]
}

---
%        00000001                             # `a`
00 * 7                                        # padding to 64-bit alignment for `b`
%%%%%%%% 10111110 10111010 11111110 11001010  # `b`
         11101111 10111110 10101101 11011110

---
a: 1
b: [1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0]

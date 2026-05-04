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
        "length": 16,
        "byte-order": "little-endian",
        "alignment": 16
      }
    }
  ]
}

---
%  00000001           # `a`
%  00000000           # padding to 16-bit alignment for `b`
%% 11111110 11001010  # `b`

---
a: 1
b: [1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0]

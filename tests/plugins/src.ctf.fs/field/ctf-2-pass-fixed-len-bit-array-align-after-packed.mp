---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
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
%  0000               # 4 bits of padding before `a`
   1011               # `a` (low 4 bits)
%  00000000           # remaining padding to 16-bit alignment for `b`
%% 11101111 10111110  # `b`

---
a: [1, 0, 1, 1]
b: [1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1]

---
{
  "type": "static-length-array",
  "length": 3,
  "element-field-class": {
    "type": "fixed-length-bit-array",
    "length": 8,
    "byte-order": "little-endian",
    "alignment": 8
  }
}

---
%00000001
%10101010
%11110000

---
- [0, 0, 0, 0, 0, 0, 0, 1]
- [1, 0, 1, 0, 1, 0, 1, 0]
- [1, 1, 1, 1, 0, 0, 0, 0]

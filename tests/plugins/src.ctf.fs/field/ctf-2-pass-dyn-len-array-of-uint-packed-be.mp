---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len"]},
        "element-field-class": {
          "type": "fixed-length-unsigned-integer",
          "length": 1,
          "byte-order": "big-endian",
          "alignment": 1
        }
      }
    }
  ]
}

---
$8          # `len`
%10101010   # `arr`

---
len: 8
arr:
  - 1
  - 0
  - 1
  - 0
  - 1
  - 0
  - 1
  - 0

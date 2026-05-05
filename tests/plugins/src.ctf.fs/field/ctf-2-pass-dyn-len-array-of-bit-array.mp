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
          "type": "fixed-length-bit-array",
          "length": 8,
          "byte-order": "little-endian",
          "alignment": 8
        }
      }
    }
  ]
}

---
$3          # `len`
%00000001   # `arr[0]`
%10101010   # `arr[1]`
%11110000   # `arr[2]`

---
len: 3
arr:
  - [0, 0, 0, 0, 0, 0, 0, 1]
  - [1, 0, 1, 0, 1, 0, 1, 0]
  - [1, 1, 1, 1, 0, 0, 0, 0]

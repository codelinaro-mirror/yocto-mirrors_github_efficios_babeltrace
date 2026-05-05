---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "arr_u",
      "field-class": {
        "type": "static-length-array",
        "length": 1,
        "element-field-class": {
          "type": "fixed-length-unsigned-integer",
          "length": 4,
          "byte-order": "little-endian",
          "alignment": 1
        }
      }
    },
    {
      "name": "arr_s",
      "field-class": {
        "type": "static-length-array",
        "length": 1,
        "element-field-class": {
          "type": "fixed-length-signed-integer",
          "length": 4,
          "byte-order": "little-endian",
          "alignment": 1
        }
      }
    }
  ]
}

---
[((-3 & 0xf) << 4) | (10 & 0xf) : 8]

---
arr_u:
  - 10
arr_s:
  - -3

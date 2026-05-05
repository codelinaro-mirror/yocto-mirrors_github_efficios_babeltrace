---
{
  "type": "structure",
  "member-classes": [
    {"name": "len_u", "field-class": "u8"},
    {"name": "len_s", "field-class": "u8"},
    {
      "name": "arr_u",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len_u"]},
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
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len_s"]},
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
$1                                    # `len_u`
$1                                    # `len_s`
[((-3 & 0xf) << 4) | (10 & 0xf) : 8]  # `arr_u` (low nibble) + `arr_s` (high nibble)

---
len_u: 1
len_s: 1
arr_u:
  - 10
arr_s:
  - -3

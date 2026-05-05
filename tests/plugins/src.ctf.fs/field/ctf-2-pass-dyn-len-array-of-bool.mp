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
          "type": "fixed-length-boolean",
          "length": 8,
          "byte-order": "little-endian",
          "alignment": 8
        }
      }
    }
  ]
}

---
$3        # `len`
01 00 ff  # `arr`

---
len: 3
arr:
  - yes
  - no
  - yes

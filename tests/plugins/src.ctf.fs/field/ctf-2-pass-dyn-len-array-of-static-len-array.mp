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
          "type": "static-length-array",
          "length": 3,
          "element-field-class": "u8"
        }
      }
    }
  ]
}

---
$2        # `len`
01 02 03  # `arr[0]`
04 05 06  # `arr[1]`

---
len: 2
arr:
  -
    - 1
    - 2
    - 3
  -
    - 4
    - 5
    - 6

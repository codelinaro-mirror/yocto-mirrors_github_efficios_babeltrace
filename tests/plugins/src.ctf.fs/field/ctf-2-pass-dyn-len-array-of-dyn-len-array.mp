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
          "type": "structure",
          "member-classes": [
            {"name": "len", "field-class": "u8"},
            {
              "name": "arr",
              "field-class": {
                "type": "dynamic-length-array",
                "length-field-location": {"path": ["len"]},
                "element-field-class": "u8"
              }
            }
          ]
        }
      }
    }
  ]
}

---
$2          # outer `len`
  # outer `arr[0]`
  $2        # inner `len`
  01 02     # inner `arr`

  # outer `arr[1]`
  $3        # inner `len`
  01 02 03  # inner `arr`

---
len: 2
arr:
  - len: 2
    arr:
      - 1
      - 2
  - len: 3
    arr:
      - 1
      - 2
      - 3

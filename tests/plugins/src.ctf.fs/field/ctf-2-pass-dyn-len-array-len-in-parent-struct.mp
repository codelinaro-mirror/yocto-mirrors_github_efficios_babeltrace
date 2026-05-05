---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "inner",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {
            "name": "arr",
            "field-class": {
              "type": "dynamic-length-array",
              "length-field-location": {"path": [null, "len"]},
              "element-field-class": "u8"
            }
          }
        ]
      }
    }
  ]
}

---
$3        # `len`
01 02 03  # `inner.arr`

---
len: 3
inner:
  arr:
    - 1
    - 2
    - 3

---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {"name": "between", "field-class": "u32le"},
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

---
$3            # `len`
[51966:32le]  # `between`
01 02 03      # `arr`

---
len: 3
between: 51966
arr:
  - 1
  - 2
  - 3

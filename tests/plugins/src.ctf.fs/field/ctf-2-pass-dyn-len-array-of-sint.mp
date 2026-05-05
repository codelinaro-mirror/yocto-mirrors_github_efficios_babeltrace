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
        "element-field-class": "i16be"
      }
    }
  ]
}

---
$3            # `len`
[-1:16be]     # `arr[0]`
[0:16be]      # `arr[1]`
[1234:16be]   # `arr[2]`

---
len: 3
arr:
  - -1
  - 0
  - 1234

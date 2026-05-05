---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "meta",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {"name": "len", "field-class": "u8"}
        ]
      }
    },
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["meta", "len"]},
        "element-field-class": "u8"
      }
    }
  ]
}

---
$3        # `meta.len`
01 02 03  # `arr`

---
meta:
  len: 3
arr:
  - 1
  - 2
  - 3

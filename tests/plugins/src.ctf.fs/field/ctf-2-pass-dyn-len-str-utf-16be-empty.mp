---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-16be",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
$0  # `len`

---
len: 0
str: ""

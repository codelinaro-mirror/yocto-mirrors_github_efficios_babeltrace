---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-32le",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
$40                   # `len`
u32le"café 日本語 🎉"  # `str`

---
len: 40
str: "café 日本語 🎉"

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
$22                    # `len`
u16be"café 日本語 🎉"   # `str`

---
len: 22
str: "café 日本語 🎉"

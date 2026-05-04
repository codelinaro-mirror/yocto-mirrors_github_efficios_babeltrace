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
$32                                     # `len`
u32le"salut!" 00 00 00 00 ab cd ef 12   # `str`

---
len: 32
str: "salut!"

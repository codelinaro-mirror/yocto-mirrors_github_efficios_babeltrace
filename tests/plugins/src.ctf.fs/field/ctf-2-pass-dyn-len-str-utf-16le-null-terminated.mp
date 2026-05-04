---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-16le",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
$18                               # `len`
u16le"salut!" 00 00 ab cd ef 12   # `str`

---
len: 18
str: "salut!"

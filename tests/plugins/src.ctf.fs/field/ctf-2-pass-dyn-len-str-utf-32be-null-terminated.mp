---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-32be",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
$32                                     # `len`
u32be"salut!" 00 00 00 00 ab cd ef 12   # `str`

---
len: 32
str: "salut!"

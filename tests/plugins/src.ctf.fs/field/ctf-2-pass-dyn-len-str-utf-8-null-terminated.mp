---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-8",
        "length-field-location": {
          "origin": "event-record-payload",
          "path": ["root", "len"]
        }
      }
    }
  ]
}

---
$16                                     # `len`
"salut!" 00 ab cd ef 12 34 56 78 9a bc  # `str`

---
len: 16
str: "salut!"

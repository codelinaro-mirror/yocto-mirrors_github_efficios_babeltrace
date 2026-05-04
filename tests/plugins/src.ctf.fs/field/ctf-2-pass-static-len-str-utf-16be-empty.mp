---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "str",
      "field-class": {
        "type": "static-length-string",
        "length": 0,
        "encoding": "utf-16be"
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
$42   # `tail`

---
str: ""
tail: 42

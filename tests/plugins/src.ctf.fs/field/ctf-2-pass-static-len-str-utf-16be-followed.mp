---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "before",
      "field-class": {
        "type": "static-length-string",
        "length": 12,
        "encoding": "utf-16be"
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
u16be"salut!"   # `before`
$42             # `after`

---
before: "salut!"
after: 42

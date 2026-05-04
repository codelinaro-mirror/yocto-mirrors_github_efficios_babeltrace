---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "before",
      "field-class": {
        "type": "static-length-string",
        "length": 24,
        "encoding": "utf-32le"
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
u32le"salut!"   # `before`
$42             # `after`

---
before: "salut!"
after: 42

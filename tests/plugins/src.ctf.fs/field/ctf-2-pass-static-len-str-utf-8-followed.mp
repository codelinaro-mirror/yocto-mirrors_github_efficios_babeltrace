---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "before",
      "field-class": {
        "type": "static-length-string",
        "length": 6,
        "encoding": "utf-8"
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
"salut!"  # `before`
$42       # `after`

---
before: "salut!"
after: 42

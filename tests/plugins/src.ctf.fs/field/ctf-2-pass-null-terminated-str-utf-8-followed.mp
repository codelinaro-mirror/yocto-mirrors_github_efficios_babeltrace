---
{
  "type": "structure",
  "member-classes": [
    {"name": "before", "field-class": "nt-str-utf-8"},
    {"name": "after",  "field-class": "u8"}
  ]
}

---
"salut!" 00   # `before`
$42           # `after`

---
before: "salut!"
after: 42

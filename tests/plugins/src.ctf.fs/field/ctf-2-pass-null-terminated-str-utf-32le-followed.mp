---
{
  "type": "structure",
  "member-classes": [
    {"name": "before", "field-class": "nt-str-utf-32le"},
    {"name": "after",  "field-class": "u8"}
  ]
}

---
u32le"salut!" 00 00 00 00   # `before`
$42                         # `after`

---
before: "salut!"
after: 42

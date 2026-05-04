---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "before",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-16be",
        "length-field-location": {"path": ["len"]}
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
$12             # `len`
u16be"salut!"   # `before`
$42             # `after`

---
len: 12
before: "salut!"
after: 42

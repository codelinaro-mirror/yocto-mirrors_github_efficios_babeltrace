---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "before",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-32be",
        "length-field-location": {"path": ["len"]}
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
$24             # `len`
u32be"salut!"   # `before`
$42             # `after`

---
len: 24
before: "salut!"
after: 42

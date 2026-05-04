---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "before",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-8",
        "length-field-location": {
          "origin": "event-record-payload",
          "path": ["root", "len"]
        }
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
$6        # `len`
"salut!"  # `before`
$42       # `after`

---
len: 6
before: "salut!"
after: 42

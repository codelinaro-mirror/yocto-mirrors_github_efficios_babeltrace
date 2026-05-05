---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "s",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {"name": "a", "field-class": "u16le"},
          {"name": "b", "field-class": "u8"}
        ]
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
[1234:16le]   # `s.a`
$5            # `s.b`
$77           # `tail`

---
s:
  a: 1234
  b: 5
tail: 77

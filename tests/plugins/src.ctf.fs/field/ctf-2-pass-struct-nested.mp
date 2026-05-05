---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "inner",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {"name": "a", "field-class": "u8"},
          {"name": "b", "field-class": "u16le"}
        ]
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
$1          # `inner.a`
[770:16le]  # `inner.b`
$9          # `tail`

---
inner:
  a: 1
  b: 770
tail: 9

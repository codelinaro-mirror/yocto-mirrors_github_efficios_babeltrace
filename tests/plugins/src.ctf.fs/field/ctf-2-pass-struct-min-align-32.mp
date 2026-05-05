---
{
  "type": "structure",
  "member-classes": [
    {"name": "lead", "field-class": "u8"},
    {
      "name": "aligned",
      "field-class": {
        "type": "structure",
        "minimum-alignment": 32,
        "member-classes": [
          {"name": "a", "field-class": "u8"},
          {"name": "b", "field-class": "u8"}
        ]
      }
    }
  ]
}

---
$5    # `lead`
@32   # 24 bits of padding before `aligned`
$10   # `aligned.a`
$20   # `aligned.b`

---
lead: 5
aligned:
  a: 10
  b: 20

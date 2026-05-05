---
{
  "type": "structure",
  "member-classes": [
    {"name": "lead", "field-class": "u8"},
    {
      "name": "aligned",
      "field-class": {
        "type": "structure",
        "minimum-alignment": 64,
        "member-classes": [
          {"name": "a", "field-class": "u16le"},
          {"name": "b", "field-class": "u16le"}
        ]
      }
    }
  ]
}

---
$7          # `lead`
@64         # 56 bits of padding before `aligned`
[100:16le]  # `aligned.a`
[200:16le]  # `aligned.b`

---
lead: 7
aligned:
  a: 100
  b: 200

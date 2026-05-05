---
{
  "type": "structure",
  "member-classes": [
    {"name": "a", "field-class": "u8"},
    {
      "name": "pad",
      "field-class": {
        "type": "structure",
        "minimum-alignment": 64,
        "member-classes": []
      }
    },
    {"name": "b", "field-class": "u32le"}
  ]
}

---
$1                # `a`
@64               # 56 bits of padding inserted to honor alignment of `pad`
[12345678:32le]   # `b`

---
a: 1
pad: ∅
b: 12345678

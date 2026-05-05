---
{
  "type": "structure",
  "member-classes": [
    {"name": "lead", "field-class": "u8"},
    {
      "name": "s",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {
            "name": "x",
            "field-class": {
              "type": "fixed-length-unsigned-integer",
              "length": 32,
              "byte-order": "little-endian",
              "alignment": 32
            }
          },
          {"name": "y", "field-class": "u8"}
        ]
      }
    }
  ]
}

---
$1          # `lead`
@32         # 24 bits of padding because `s` inherits alignment of `s.x`
[42:32le]   # `s.x`
$5          # `s.y`

---
lead: 1
s:
  x: 42
  y: 5

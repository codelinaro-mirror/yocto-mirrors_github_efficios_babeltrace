---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "nibble",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "s",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {"name": "a", "field-class": "u8"},
          {"name": "b", "field-class": "u8"}
        ]
      }
    }
  ]
}

---
[5:8le]   # `nibble` (low nibble) + 4 bits of padding to align `s` to 8
$10       # `s.a`
$20       # `s.b`

---
nibble: 5
s:
  a: 10
  b: 20

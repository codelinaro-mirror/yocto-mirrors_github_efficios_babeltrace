---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": "u8le"
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 32,
        "byte-order": "little-endian",
        "alignment": 32
      }
    }
  ]
}

---
$1                  # `a`
12 34 45            # padding to 32-bit alignment for `b`
[2864434397:32le]   # `b`

---
a: 1
b: yes

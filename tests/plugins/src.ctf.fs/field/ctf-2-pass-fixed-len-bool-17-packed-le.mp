---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 3,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 17,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
[(9 << 20) | 5 : 24le]

---
a: yes
b: no
c: yes

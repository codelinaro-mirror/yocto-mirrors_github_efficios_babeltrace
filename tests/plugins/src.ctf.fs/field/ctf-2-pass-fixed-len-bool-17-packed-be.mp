---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 3,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 17,
        "byte-order": "big-endian",
        "alignment": 1
      }
    },
    {
      "name": "c",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 4,
        "byte-order": "big-endian",
        "alignment": 1
      }
    }
  ]
}

---
[(5 << 21) | 9 : 24be]

---
a: yes
b: no
c: yes

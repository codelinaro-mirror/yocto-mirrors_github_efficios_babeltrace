---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "sel",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 8,
        "byte-order": "little-endian",
        "alignment": 8
      }
    },
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "field-class": {
          "type": "static-length-array",
          "length": 3,
          "element-field-class": "u16le"
        }
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
01                        # `sel`
[10:16] [20:16] [30:16]   # `opt`
$42                       # `tail`

---
sel: yes
opt:
  - 10
  - 20
  - 30
tail: 42

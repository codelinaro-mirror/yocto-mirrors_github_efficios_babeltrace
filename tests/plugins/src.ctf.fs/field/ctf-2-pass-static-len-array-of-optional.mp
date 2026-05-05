---
{
  "type": "static-length-array",
  "length": 3,
  "element-field-class": {
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
          "field-class": "u16le"
        }
      }
    ]
  }
}

---
# first element
01          # `sel` (enabled)
[1995:16]   # `opt`

# second element
00          # `sel` (disabled)

# third element
01          # `sel` (enabled)
[42:16]     # `opt`

---
- sel: yes
  opt: 1995
- sel: no
  opt: ~
- sel: yes
  opt: 42

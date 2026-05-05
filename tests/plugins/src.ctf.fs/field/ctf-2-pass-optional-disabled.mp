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
        "field-class": "nt-str-utf-8"
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
00    # `sel`
$42   # `tail`

---
sel: no
opt: ~
tail: 42

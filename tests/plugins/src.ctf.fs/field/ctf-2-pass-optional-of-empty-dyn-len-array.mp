---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
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
          "type": "dynamic-length-array",
          "length-field-location": {"path": ["len"]},
          "element-field-class": "u8"
        }
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
$0    # `len`
01    # `sel`
$42   # `tail`

---
len: 0
sel: yes
opt: ∅
tail: 42

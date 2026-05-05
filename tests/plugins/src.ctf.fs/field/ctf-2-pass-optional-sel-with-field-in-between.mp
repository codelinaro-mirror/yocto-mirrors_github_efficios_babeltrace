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
    {"name": "between", "field-class": "u32le"},
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "field-class": "nt-str-utf-8"
      }
    }
  ]
}

---
01            # `sel`
[51966:32le]  # `between`
"Quebec\0"    # `opt`

---
sel: yes
between: 51966
opt: "Quebec"

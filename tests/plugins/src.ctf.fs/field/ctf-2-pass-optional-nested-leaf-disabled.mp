---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "outer_sel",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 8,
        "byte-order": "little-endian",
        "alignment": 8
      }
    },
    {
      "name": "inner_sel",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 8,
        "byte-order": "little-endian",
        "alignment": 8
      }
    },
    {
      "name": "outer_opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["outer_sel"]},
        "field-class": {
          "type": "optional",
          "selector-field-location": {"path": ["inner_sel"]},
          "field-class": "u8"
        }
      }
    }
  ]
}

---
01  # `outer_sel`
00  # `inner_sel`

---
outer_sel: yes
inner_sel: no
outer_opt: ~

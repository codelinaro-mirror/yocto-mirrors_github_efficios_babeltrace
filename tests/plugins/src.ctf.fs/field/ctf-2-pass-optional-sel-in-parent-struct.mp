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
      "name": "inner",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {
            "name": "opt",
            "field-class": {
              "type": "optional",
              "selector-field-location": {"path": [null, "sel"]},
              "field-class": "nt-str-utf-8"
            }
          }
        ]
      }
    }
  ]
}

---
01          # `sel`
"salut\0"   # `inner.opt`

---
sel: yes
inner:
  opt: "salut"

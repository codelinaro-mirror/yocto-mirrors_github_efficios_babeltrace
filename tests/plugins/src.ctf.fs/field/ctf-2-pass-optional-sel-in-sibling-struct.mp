---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "meta",
      "field-class": {
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
          }
        ]
      }
    },
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["meta", "sel"]},
        "field-class": "nt-str-utf-8"
      }
    }
  ]
}

---
01            # `meta.sel`
"patente\0"   # `opt`

---
meta:
  sel: yes
opt: "patente"

---
{
  "type": "structure",
  "member-classes": [
    {"name": "sel", "field-class": "u16le"},
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "selector-field-ranges": [[10, 20], [100, 200], [1000, 2000]],
        "field-class": {
          "type": "variant",
          "selector-field-location": {"path": ["sel"]},
          "options": [
            {"selector-field-ranges": [[10, 20]], "field-class": "u8"},
            {"selector-field-ranges": [[100, 200]], "field-class": "nt-str-utf-8"},
            {"selector-field-ranges": [[1000, 2000]], "field-class": "flt32le"}
          ]
        }
      }
    }
  ]
}

---
[1500:16le]   # `sel`
[2.5:32le]    # `opt` (third option)

---
sel: 1500
opt: 2.500000

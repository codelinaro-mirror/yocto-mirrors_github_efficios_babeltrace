---
{
  "type": "structure",
  "member-classes": [
    {"name": "sel", "field-class": "i8"},
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "selector-field-ranges": [[-50, -10]],
        "field-class": "nt-str-utf-8"
      }
    }
  ]
}

---
$-25          # `sel`
"chilly\0"    # `opt`

---
sel: -25
opt: "chilly"

---
{
  "type": "structure",
  "member-classes": [
    {"name": "sel", "field-class": "u8"},
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "selector-field-ranges": [[10, 20]],
        "field-class": "nt-str-utf-8"
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
$15       # `sel`
"meow\0"  # `opt`
$42       # `tail`

---
sel: 15
opt: "meow"
tail: 42

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
$5    # `sel`
$42   # `tail`

---
sel: 5
opt: ~
tail: 42

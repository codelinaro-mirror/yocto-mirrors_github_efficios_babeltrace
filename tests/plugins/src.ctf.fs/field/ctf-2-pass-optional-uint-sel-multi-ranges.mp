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
        "selector-field-ranges": [[1, 3], [100, 200]],
        "field-class": "nt-str-utf-8"
      }
    }
  ]
}

---
$150    # `sel`
"hi\0"  # `opt`

---
sel: 150
opt: "hi"

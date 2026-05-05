---
{
  "type": "structure",
  "member-classes": [
    {"name": "tag", "field-class": "i8"},
    {
      "name": "var",
      "field-class": {
        "type": "variant",
        "selector-field-location": {"path": ["tag"]},
        "options": [
          {"selector-field-ranges": [[-50, -10]], "field-class": "nt-str-utf-8"},
          {"selector-field-ranges": [[0, 100]], "field-class": "u16le"}
        ]
      }
    }
  ]
}

---
$-25        # `tag`
"chilly\0"  # `var`

---
tag: -25
var: "chilly"

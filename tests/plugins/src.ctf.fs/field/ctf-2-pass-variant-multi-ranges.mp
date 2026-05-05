---
{
  "type": "structure",
  "member-classes": [
    {"name": "tag", "field-class": "u8"},
    {
      "name": "var",
      "field-class": {
        "type": "variant",
        "selector-field-location": {"path": ["tag"]},
        "options": [
          {
            "selector-field-ranges": [[1, 3], [100, 200]],
            "field-class": "nt-str-utf-8"
          },
          {
            "selector-field-ranges": [[10, 20], [240, 255]],
            "field-class": "u16le"
          }
        ]
      }
    }
  ]
}

---
$150    # `tag`
"hi\0"  # `var`

---
tag: 150
var: "hi"

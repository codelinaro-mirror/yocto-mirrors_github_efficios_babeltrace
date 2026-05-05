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
          {"selector-field-ranges": [[0, 0]], "field-class": "u32le"}
        ]
      }
    }
  ]
}

---
00                  # `tag`
[3735928559:32le]   # `var`

---
tag: 0
var: 3735928559

---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "meta",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {"name": "tag", "field-class": "u8"}
        ]
      }
    },
    {
      "name": "var",
      "field-class": {
        "type": "variant",
        "selector-field-location": {"path": ["meta", "tag"]},
        "options": [
          {"selector-field-ranges": [[0, 0]], "field-class": "u16le"},
          {"selector-field-ranges": [[1, 1]], "field-class": "u8"}
        ]
      }
    }
  ]
}

---
00          # `meta.tag`
[1995:16]   # `var`

---
meta:
  tag: 0
var: 1995

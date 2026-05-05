---
{
  "type": "structure",
  "member-classes": [
    {"name": "tag", "field-class": "u8"},
    {"name": "between", "field-class": "u32le"},
    {
      "name": "var",
      "field-class": {
        "type": "variant",
        "selector-field-location": {"path": ["tag"]},
        "options": [
          {"selector-field-ranges": [[0, 0]], "field-class": "u16le"},
          {"selector-field-ranges": [[1, 1]], "field-class": "u8"}
        ]
      }
    }
  ]
}

---
00            # `tag`
[51966:32le]  # `between`
[1995:16]     # `var`

---
tag: 0
between: 51966
var: 1995

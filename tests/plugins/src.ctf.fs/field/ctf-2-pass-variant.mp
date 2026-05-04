---
{
  "type": "static-length-array",
  "length": 2,
  "element-field-class": {
    "type": "structure",
    "member-classes": [
      {"name": "tag", "field-class": "u8"},
      {
        "name": "var",
        "field-class": {
          "type": "variant",
          "selector-field-location": {
            "origin": "event-record-payload",
            "path": ["root", "tag"]
          },
          "options": [
            {"selector-field-ranges": [[0, 0]], "field-class": "u16le"},
            {"selector-field-ranges": [[1, 1]], "field-class": "nt-str-utf-8"}
          ]
        }
      }
    ]
  }
}

---
00                # `tag`
[1995:16]         # `var`

01                # `tag`
"hello there!\0"  # `var`

---
- tag: 0
  var: 1995
- tag: 1
  var: "hello there!"

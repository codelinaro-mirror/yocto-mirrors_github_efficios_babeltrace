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
          "selector-field-location": {"path": ["tag"]},
          "options": [
            {
              "selector-field-ranges": [[0, 0]],
              "field-class": {
                "type": "structure",
                "member-classes": [
                  {"name": "x", "field-class": "u8"},
                  {"name": "y", "field-class": "u16le"}
                ]
              }
            },
            {"selector-field-ranges": [[1, 1]], "field-class": "nt-str-utf-8"}
          ]
        }
      }
    ]
  }
}

---
# first element
00            # `tag`
$10           # `var.x`
[2000:16]     # `var.y`

# second element
01            # `tag`
"bonjour\0"   # `var`

---
- tag: 0
  var:
    x: 10
    y: 2000
- tag: 1
  var: "bonjour"

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
                "type": "static-length-array",
                "length": 3,
                "element-field-class": "u16le"
              }
            },
            {"selector-field-ranges": [[1, 1]], "field-class": "u8"}
          ]
        }
      }
    ]
  }
}

---
# first element
00                        # `tag`
[10:16] [20:16] [30:16]   # `var` (array field of three `u16le`)

# second element
01                        # `tag`
$42                       # `var`

---
- tag: 0
  var:
    - 10
    - 20
    - 30
- tag: 1
  var: 42

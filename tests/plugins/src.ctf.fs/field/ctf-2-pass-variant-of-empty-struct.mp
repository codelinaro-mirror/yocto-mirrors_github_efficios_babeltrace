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
                "member-classes": []
              }
            },
            {"selector-field-ranges": [[1, 1]], "field-class": "u8"}
          ]
        }
      },
      {"name": "after", "field-class": "u8"}
    ]
  }
}

---
# first element
00    # `tag`
$42   # `after`

# second element
01    # `tag`
$77   # `var`
$99   # `after`

---
- tag: 0
  var: ∅
  after: 42
- tag: 1
  var: 77
  after: 99

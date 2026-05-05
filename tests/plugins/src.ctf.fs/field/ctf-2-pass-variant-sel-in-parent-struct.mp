---
{
  "type": "structure",
  "member-classes": [
    {"name": "tag", "field-class": "u8"},
    {
      "name": "inner",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {
            "name": "var",
            "field-class": {
              "type": "variant",
              "selector-field-location": {"path": [null, "tag"]},
              "options": [
                {"selector-field-ranges": [[0, 0]], "field-class": "u16le"},
                {"selector-field-ranges": [[1, 1]], "field-class": "u8"}
              ]
            }
          }
        ]
      }
    }
  ]
}

---
00          # `tag`
[1995:16]   # `inner.var`

---
tag: 0
inner:
  var: 1995

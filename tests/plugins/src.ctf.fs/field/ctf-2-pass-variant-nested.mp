---
{
  "type": "static-length-array",
  "length": 3,
  "element-field-class": {
    "type": "structure",
    "member-classes": [
      {"name": "outer_tag", "field-class": "u8"},
      {"name": "inner_tag", "field-class": "u8"},
      {
        "name": "var",
        "field-class": {
          "type": "variant",
          "selector-field-location": {"path": ["outer_tag"]},
          "options": [
            {
              "selector-field-ranges": [[0, 0]],
              "field-class": {
                "type": "variant",
                "selector-field-location": {
                  "origin": "event-record-payload",
                  "path": ["root", "inner_tag"]
                },
                "options": [
                  {"selector-field-ranges": [[0, 0]], "field-class": "u8"},
                  {"selector-field-ranges": [[1, 1]], "field-class": "u16le"}
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
00          # `outer_tag`
00          # `inner_tag`
$77         # `var` (`u8`)

# second element
00          # `outer_tag`
01          # `inner_tag`
[2024:16]   # `var` (`u16le`)

# third element
01          # `outer_tag`
00          # `inner_tag`
"yo!\0"     # `var` (`nt-str-utf-8`)

---
- outer_tag: 0
  inner_tag: 0
  var: 77
- outer_tag: 0
  inner_tag: 1
  var: 2024
- outer_tag: 1
  inner_tag: 0
  var: "yo!"

---
{
  "type": "structure",
  "member-classes": [
    {"name": "before", "field-class": "u8"},
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
              "type": "fixed-length-unsigned-integer",
              "length": 32,
              "byte-order": "little-endian",
              "alignment": 32
            }
          }
        ]
      }
    },
    {"name": "after", "field-class": "u8"}
  ]
}

---
ab                  # `before`
00                  # `tag`
@32                 # padding to 32-bit boundary (driven by inner 32-bit)
[3735928559:32le]   # `var`
$42                 # `after`

---
before: 171
tag: 0
var: 3735928559
after: 42

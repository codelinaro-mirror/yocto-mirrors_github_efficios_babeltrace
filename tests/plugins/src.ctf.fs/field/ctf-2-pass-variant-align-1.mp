---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "pre",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 5,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "tag",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 2,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
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
              "length": 1,
              "byte-order": "little-endian",
              "alignment": 1
            }
          },
          {
            "selector-field-ranges": [[1, 1]],
            "field-class": {
              "type": "fixed-length-unsigned-integer",
              "length": 1,
              "byte-order": "little-endian",
              "alignment": 1
            }
          }
        ]
      }
    }
  ]
}

---
%
  1       # `var` (bit 7, MSB)
  00      # `tag`
  10110   # `pre` (LSBs)

---
pre: 22
tag: 0
var: 1

---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "sel",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "var",
      "field-class": {
        "type": "variant",
        "selector-field-location": {"path": ["sel"]},
        "options": [
          {"selector-field-ranges": [[0, 0]], "field-class": "nt-str-utf-8"},
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
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 1,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "pad",
      "field-class": {
        "type": "fixed-length-unsigned-integer",
        "length": 4,
        "byte-order": "little-endian",
        "alignment": 1
      }
    }
  ]
}

---
%
  0000  # `pad` (bits 7..4)
  1     # `b`   (bit 3)
  1     # `var` (bit 2)
  0     # `a`   (bit 1)
  1     # `sel` (bit 0, LSB)

---
sel: 1
a: 0
var: 1
b: 1
pad: 0

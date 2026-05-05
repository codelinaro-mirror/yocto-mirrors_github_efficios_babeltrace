---
{
  "type": "structure",
  "member-classes": [
    {"name": "before", "field-class": "u8"},
    {
      "name": "sel",
      "field-class": {
        "type": "fixed-length-boolean",
        "length": 8,
        "byte-order": "little-endian",
        "alignment": 8
      }
    },
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "field-class": {
          "type": "fixed-length-unsigned-integer",
          "length": 32,
          "byte-order": "little-endian",
          "alignment": 32
        }
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
ab                  # `before`
01                  # `sel`
@32                 # padding to 32-bit boundary (driven by inner 32-bit)
[3735928559:32le]   # `opt`
$42                 # `tail`

---
before: 171
sel: yes
opt: 3735928559
tail: 42

---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len"]},
        "element-field-class": {
          "type": "structure",
          "member-classes": [
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
                "field-class": "u16le"
              }
            }
          ]
        }
      }
    }
  ]
}

---
$3          # `len`

# first element
01          # `sel`
[1995:16]   # `opt`

# second element
00          # `sel`

# third element
01          # `sel`
[42:16]     # `opt`

---
len: 3
arr:
  - sel: yes
    opt: 1995
  - sel: no
    opt: ~
  - sel: yes
    opt: 42

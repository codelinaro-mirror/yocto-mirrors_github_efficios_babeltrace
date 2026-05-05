---
{
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
        "field-class": {
          "type": "structure",
          "member-classes": [
            {"name": "a", "field-class": "u8"},
            {"name": "b", "field-class": "nt-str-utf-8"},
            {"name": "c", "field-class": "u16le"}
          ]
        }
      }
    }
  ]
}

---
01            # `sel`
$7            # `opt.a`
"yo\0"        # `opt.b`
[1234:16le]   # `opt.c`

---
sel: yes
opt:
  a: 7
  b: "yo"
  c: 1234

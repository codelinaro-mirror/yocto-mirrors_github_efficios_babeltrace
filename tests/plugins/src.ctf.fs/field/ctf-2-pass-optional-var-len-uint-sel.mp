---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "sel",
      "field-class": {"type": "variable-length-unsigned-integer"}
    },
    {
      "name": "opt",
      "field-class": {
        "type": "optional",
        "selector-field-location": {"path": ["sel"]},
        "selector-field-ranges": [[10, 20]],
        "field-class": "u16le"
      }
    },
    {"name": "tail", "field-class": "u8"}
  ]
}

---
[15:uleb128]  # `sel`
[1995:16]     # `opt`
$42           # `tail`

---
sel: 15
opt: 1995
tail: 42

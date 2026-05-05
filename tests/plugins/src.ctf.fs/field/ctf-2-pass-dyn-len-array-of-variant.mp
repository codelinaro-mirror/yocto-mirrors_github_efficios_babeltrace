---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {"name": "tag", "field-class": "u8"},
    {
      "name": "arr",
      "field-class": {
        "type": "dynamic-length-array",
        "length-field-location": {"path": ["len"]},
        "element-field-class": {
          "type": "variant",
          "selector-field-location": {"path": ["tag"]},
          "options": [
            {"selector-field-ranges": [[0, 0]], "field-class": "u16le"},
            {"selector-field-ranges": [[1, 1]], "field-class": "nt-str-utf-8"}
          ]
        }
      }
    }
  ]
}

---
$3                            # `len`
00                            # `tag`
[1995:16] [42:16] [1234:16]   # `arr` (3 × `u16le`)

---
len: 3
tag: 0
arr:
  - 1995
  - 42
  - 1234

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
            {"name": "a", "field-class": "u8le"},
            {"name": "b", "field-class": "nt-str-utf-8"}
          ]
        }
      }
    }
  ]
}

---
$3            # `len`

01            # `a`
"salut\0"     # `b`

02            # `a`
"patente\0"   # `b`

03            # `a`
"Quebec\0"    # `b`

---
len: 3
arr:
  - a: 1
    b: "salut"
  - a: 2
    b: "patente"
  - a: 3
    b: "Quebec"

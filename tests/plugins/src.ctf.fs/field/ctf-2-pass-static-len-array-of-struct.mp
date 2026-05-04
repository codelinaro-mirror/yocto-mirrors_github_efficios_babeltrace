---
{
  "type": "static-length-array",
  "length": 2,
  "element-field-class": {
    "type": "structure",
    "member-classes": [
      {
        "name": "x",
        "field-class": {
          "type": "static-length-array",
          "length": 3,
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
}

---
01              # `a`
"salut\0"       # `b`

02              # `a`
"patente\0"     # `b`

03              # `a`
"Quebec\0"      # `b`

04              # `a`
"chez nous\0"   # `b`

05              # `a`
"aidez-moi\0"   # `b`

06              # `a`
"rasseye\0"     # `b`

---
- x:
  - a: 1
    b: "salut"
  - a: 2
    b: "patente"
  - a: 3
    b: "Quebec"
- x:
  - a: 4
    b: "chez nous"
  - a: 5
    b: "aidez-moi"
  - a: 6
    b: "rasseye"

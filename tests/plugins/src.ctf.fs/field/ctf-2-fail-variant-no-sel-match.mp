---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "sel",
      "field-class": "u8le"
    },
    {
      "name": "var",
      "field-class": {
        "type": "variant",
        "selector-field-location": {"path": ["sel"]},
        "options": [
          {"selector-field-ranges": [[0, 0]], "field-class": "u8le"},
          {"selector-field-ranges": [[1, 1]], "field-class": "u16le"}
        ]
      }
    }
  ]
}

---
05      # `sel` (no option matches)
00 00

---
no variant field option selected by the selector value 5

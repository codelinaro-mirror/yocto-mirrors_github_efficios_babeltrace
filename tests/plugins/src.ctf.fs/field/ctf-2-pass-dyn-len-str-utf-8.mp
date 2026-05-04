---
{
  "type": "structure",
  "member-classes": [
    {"name": "len", "field-class": "u8"},
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-8",
        "length-field-location": {
          "origin": "event-record-payload",
          "path": ["root", "len"]
        }
      }
    }
  ]
}

---
$20                # `len`
"café 日本語 🎉"  # `str`

---
len: 20
str: "café 日本語 🎉"

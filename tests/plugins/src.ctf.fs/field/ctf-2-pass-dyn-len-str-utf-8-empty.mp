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
$0  # `len`

---
len: 0
str: ""

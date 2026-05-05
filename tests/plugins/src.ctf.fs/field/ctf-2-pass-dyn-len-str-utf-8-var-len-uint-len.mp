---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "len",
      "field-class": {"type": "variable-length-unsigned-integer"}
    },
    {
      "name": "str",
      "field-class": {
        "type": "dynamic-length-string",
        "encoding": "utf-8",
        "length-field-location": {"path": ["len"]}
      }
    }
  ]
}

---
[5:uleb128]   # `len`
"meow!"     # `str`

---
len: 5
str: "meow!"

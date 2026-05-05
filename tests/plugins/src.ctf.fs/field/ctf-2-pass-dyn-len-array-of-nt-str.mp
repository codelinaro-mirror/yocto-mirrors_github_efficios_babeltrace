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
        "element-field-class": "nt-str-utf-8"
      }
    }
  ]
}

---
$3          # `len`
"hello\0"   # `arr[0]`
"world\0"   # `arr[1]`
"!\0"       # `arr[2]`

---
len: 3
arr:
  - "hello"
  - "world"
  - "!"

---
{
  "type": "structure",
  "member-classes": [
    {"name": "meow", "field-class": "i16le"},
    {"name": "mix",  "field-class": "nt-str-utf-8"},
    {"name": "cat",  "field-class": "flt32le"}
  ]
}

---
[-1717:16]        # `meow`
"rapidement!\0"   # `mix`
[2.897771955:32]  # `cat`

---
meow: -1717
mix: "rapidement!"
cat: 2.897772

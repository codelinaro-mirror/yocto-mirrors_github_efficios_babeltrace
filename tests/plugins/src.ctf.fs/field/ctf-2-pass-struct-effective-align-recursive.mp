---
{
  "type": "structure",
  "member-classes": [
    {"name": "lead", "field-class": "u8"},
    {
      "name": "outer",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {
            "name": "inner",
            "field-class": {
              "type": "structure",
              "member-classes": [
                {
                  "name": "z",
                  "field-class": {
                    "type": "fixed-length-unsigned-integer",
                    "length": 64,
                    "byte-order": "little-endian",
                    "alignment": 64
                  }
                }
              ]
            }
          },
          {"name": "q", "field-class": "u8"}
        ]
      }
    }
  ]
}

---
$1                # `lead`
@64               # 56 bits of padding: `outer` inherits alignment of `outer.inner.z`
[123456789:64le]  # `outer.inner.z`
$7                # `outer.q`

---
lead: 1
outer:
  inner:
    z: 123456789
  q: 7

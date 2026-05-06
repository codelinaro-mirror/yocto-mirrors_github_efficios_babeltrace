---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "a",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 5,
        "byte-order": "little-endian",
        "alignment": 1
      }
    },
    {
      "name": "b",
      "field-class": {
        "type": "fixed-length-bit-array",
        "length": 3,
        "byte-order": "big-endian",
        "alignment": 1
      }
    }
  ]
}

---
ff

---
two contiguous fixed-length bit array fields which aren't byte-aligned don't share the same byte order: little-endian followed with big-endian

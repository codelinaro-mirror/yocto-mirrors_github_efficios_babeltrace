---
{
  "type": "structure",
  "member-classes": [
    {
      "name": "l1",
      "field-class": {
        "type": "structure",
        "member-classes": [
          {
            "name": "l2",
            "field-class": {
              "type": "structure",
              "member-classes": [
                {
                  "name": "l3",
                  "field-class": {
                    "type": "structure",
                    "member-classes": [
                      {"name": "v", "field-class": "u8"}
                    ]
                  }
                }
              ]
            }
          }
        ]
      }
    }
  ]
}

---
$42

---
l1:
  l2:
    l3:
      v: 42

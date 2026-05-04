---
struct {
  integer { size = 4; align = 1; byte_order = le; } pad;
  string                                            str;
}

---
[5:8le]              # `pad` (low nibble) + 4 bits of padding
"café 日本語 🎉" 00   # `str`

---
pad: 5
str: "café 日本語 🎉"

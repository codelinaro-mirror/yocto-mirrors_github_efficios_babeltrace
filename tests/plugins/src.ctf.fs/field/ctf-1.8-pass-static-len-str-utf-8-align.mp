---
struct {
  integer { size = 4; align = 1; byte_order = le; } pad;
  integer { size = 8; align = 8; encoding = UTF8; } str[20];
}

---
[5:8le]          # `pad` (low nibble) + 4 bits of padding
"café 日本語 🎉"  # `str`

---
pad: 5
str: "café 日本語 🎉"

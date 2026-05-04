---
struct {
  integer { size = 4; align = 1; byte_order = le; } pad;
  u8                                                len;
  integer { size = 8; align = 8; encoding = UTF8; } str[len];
}

---
[5:8le]          # `pad` (low nibble) + 4 bits of padding
$20              # `len`
"café 日本語 🎉"  # `str`

---
pad: 5
len: 20
str: "café 日本語 🎉"

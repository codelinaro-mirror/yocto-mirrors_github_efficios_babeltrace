---
struct {
  u8                                                len;
  integer { size = 8; align = 8; encoding = UTF8; } str[len];
}

---
$20                # `len`
"café 日本語 🎉"  # `str`

---
len: 20
str: "café 日本語 🎉"

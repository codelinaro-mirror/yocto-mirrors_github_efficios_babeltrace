---
struct {
  u8                                                len;
  integer { size = 8; align = 8; encoding = UTF8; } str[len];
}

---
$16                                     # `len`
"salut!" 00 ab cd ef 12 34 56 78 9a bc  # `str`

---
len: 16
str: "salut!"

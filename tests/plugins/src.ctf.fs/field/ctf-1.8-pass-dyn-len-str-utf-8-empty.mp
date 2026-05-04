---
struct {
  u8                                                len;
  integer { size = 8; align = 8; encoding = UTF8; } str[len];
}

---
$0  # `len`

---
len: 0
str: ""

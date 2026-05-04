---
struct {
  integer { size = 8; align = 8; encoding = UTF8; } str[0];
  u8                                                tail;
}

---
$42   # `tail`

---
str: ""
tail: 42

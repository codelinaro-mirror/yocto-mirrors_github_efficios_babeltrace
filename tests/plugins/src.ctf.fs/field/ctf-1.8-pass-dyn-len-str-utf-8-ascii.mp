---
struct {
  u8                                                len;
  integer { size = 8; align = 8; encoding = UTF8; } str[len];
}

---
$13               # `len`
"Hello, world!"   # `str`

---
len: 13
str: "Hello, world!"

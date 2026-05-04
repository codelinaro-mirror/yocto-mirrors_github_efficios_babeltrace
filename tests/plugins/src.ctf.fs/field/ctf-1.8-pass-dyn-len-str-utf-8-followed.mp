---
struct {
  u8                                                len;
  integer { size = 8; align = 8; encoding = UTF8; } before[len];
  u8                                                after;
}

---
$6        # `len`
"salut!"  # `before`
$42       # `after`

---
len: 6
before: "salut!"
after: 42

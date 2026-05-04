---
struct {
  integer { size = 8; align = 8; encoding = UTF8; } before[6];
  u8                                                after;
}

---
"salut!"  # `before`
$42       # `after`

---
before: "salut!"
after: 42

---
struct {
  u8                                                  before;
  integer { size = 32; align = 32; byte_order = le; } arr[0];
  nt_str                                              after;
}

---
$42           # `before`
@32           # 24 bits of padding
"hello!" 00   # `after`

---
before: 42
arr: ∅
after: "hello!"

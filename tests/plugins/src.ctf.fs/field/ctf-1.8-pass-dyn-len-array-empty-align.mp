---
struct {
  u8                                                  len;
  u8                                                  before;
  integer { size = 32; align = 32; byte_order = le; } arr[len];
  nt_str                                              after;
}

---
$0            # `len`
$42           # `before`
@32           # 16 bits of padding
"hello!" 00   # `after`

---
len: 0
before: 42
arr: ∅
after: "hello!"

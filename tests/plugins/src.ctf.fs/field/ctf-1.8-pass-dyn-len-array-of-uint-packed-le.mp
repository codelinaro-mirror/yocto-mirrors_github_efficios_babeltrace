---
struct {
  u8                                                len;
  integer { size = 1; align = 1; byte_order = le; } arr[len];
}

---
$8          # `len`
%10101010   # `arr`

---
len: 8
arr:
  - 0
  - 1
  - 0
  - 1
  - 0
  - 1
  - 0
  - 1

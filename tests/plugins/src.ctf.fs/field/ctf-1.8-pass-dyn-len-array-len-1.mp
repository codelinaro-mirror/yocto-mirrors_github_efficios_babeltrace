---
struct {
  u8 len;
  u8 arr[len];
}

---
$1    # `len`
$42   # `arr`

---
len: 1
arr:
  - 42

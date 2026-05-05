---
struct {
  u8 len;
  u8 arr[len];
}

---
$4            # `len`
01 02 03 04   # `arr`

---
len: 4
arr:
  - 1
  - 2
  - 3
  - 4

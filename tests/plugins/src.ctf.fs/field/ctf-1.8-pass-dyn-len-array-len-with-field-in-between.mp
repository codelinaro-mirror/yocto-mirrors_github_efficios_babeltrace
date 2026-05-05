---
struct {
  u8    len;
  u32le between;
  u8    arr[len];
}

---
$3            # `len`
[51966:32le]  # `between`
01 02 03      # `arr`

---
len: 3
between: 51966
arr:
  - 1
  - 2
  - 3

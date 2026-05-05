---
struct {
  u8 len;

  struct {
    u8 arr[len];
  } inner;
}

---
$3        # `len`
01 02 03  # `inner.arr`

---
len: 3
inner:
  arr:
    - 1
    - 2
    - 3

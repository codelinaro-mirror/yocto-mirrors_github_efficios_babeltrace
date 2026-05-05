---
struct {
  struct {
    u8 len;
  }  meta;

  u8 arr[meta.len];
}

---
$3        # `meta.len`
01 02 03  # `arr`

---
meta:
  len: 3
arr:
  - 1
  - 2
  - 3

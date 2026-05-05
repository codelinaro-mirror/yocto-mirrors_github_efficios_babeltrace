---
struct {
  u8 len;
  u8 arr[2][len];
}

---
$3        # `len`
01 02 03  # `arr[0]`
04 05 06  # `arr[1]`

---
len: 3
arr:
  -
    - 1
    - 2
    - 3
  -
    - 4
    - 5
    - 6

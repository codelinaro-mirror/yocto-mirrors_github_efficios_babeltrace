---
struct {
  u8 len;
  u8 arr[len][3];
}

---
$2        # `len`
01 02 03  # `arr[0]`
04 05 06  # `arr[1]`

---
len: 2
arr:
  -
    - 1
    - 2
    - 3
  -
    - 4
    - 5
    - 6

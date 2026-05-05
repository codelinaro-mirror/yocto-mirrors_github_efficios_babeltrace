---
struct {
  u8 len;
  enum : u8le {
    RED,
    GREEN = 5,
    BLUE = 10,
  } arr[len];
}

---
$3        # `len`
00 05 0a  # `arr`

---
len: 3
arr:
  - 0
  - 5
  - 10

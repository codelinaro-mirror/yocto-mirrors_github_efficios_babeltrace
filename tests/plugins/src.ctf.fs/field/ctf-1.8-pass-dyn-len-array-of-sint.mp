---
struct {
  u8    len;
  i16be arr[len];
}

---
$3            # `len`
[-1:16be]     # `arr[0]`
[0:16be]      # `arr[1]`
[1234:16be]   # `arr[2]`

---
len: 3
arr:
  - -1
  - 0
  - 1234

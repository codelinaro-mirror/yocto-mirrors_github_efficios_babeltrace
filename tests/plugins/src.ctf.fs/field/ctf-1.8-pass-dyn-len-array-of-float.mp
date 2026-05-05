---
struct {
  u8      len;
  flt32le arr[len];
}

---
$3            # `len`
[3.14:32le]   # `arr[0]`
[-2.5:32le]   # `arr[1]`
[0.0:32le]    # `arr[2]`

---
len: 3
arr:
  - 3.140000
  - -2.500000
  - 0.000000

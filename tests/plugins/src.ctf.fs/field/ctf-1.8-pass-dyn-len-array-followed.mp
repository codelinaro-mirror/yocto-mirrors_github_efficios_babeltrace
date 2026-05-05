---
struct {
  u8    len;
  u16le arr[len];
  u8    tail;
}

---
$3                                # `len`
[100:16le] [200:16le] [300:16le]  # `arr`
$42                               # `tail`

---
len: 3
arr:
  - 100
  - 200
  - 300
tail: 42

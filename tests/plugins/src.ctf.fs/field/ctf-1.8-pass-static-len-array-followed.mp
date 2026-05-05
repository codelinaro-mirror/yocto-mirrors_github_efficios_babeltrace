---
struct {
  u16le arr[3];
  u8    tail;
}

---
[100:16le] [200:16le] [300:16le]  # `arr`
$42                               # `tail`

---
arr:
  - 100
  - 200
  - 300
tail: 42

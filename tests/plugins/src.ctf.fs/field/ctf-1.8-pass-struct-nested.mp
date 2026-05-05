---
struct {
  struct {
    u8    a;
    u16le b;
  }  inner;

  u8 tail;
}

---
$1          # `inner.a`
[770:16le]  # `inner.b`
$9          # `tail`

---
inner:
  a: 1
  b: 770
tail: 9

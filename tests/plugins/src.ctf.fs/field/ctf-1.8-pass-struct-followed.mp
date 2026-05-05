---
struct {
  struct {
    u16le a;
    u8    b;
  }  s;

  u8 tail;
}

---
[1234:16le]   # `s.a`
$5            # `s.b`
$77           # `tail`

---
s:
  a: 1234
  b: 5
tail: 77

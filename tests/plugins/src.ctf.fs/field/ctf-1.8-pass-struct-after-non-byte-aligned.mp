---
struct {
  integer {
    size = 4; align = 1;
    byte_order = le;
  } nibble;

  struct {
    u8 a;
    u8 b;
  } s;
}

---
[5:8le]   # `nibble` (low nibble) + 4 bits of padding to align `s` to 8
$10       # `s.a`
$20       # `s.b`

---
nibble: 5
s:
  a: 10
  b: 20

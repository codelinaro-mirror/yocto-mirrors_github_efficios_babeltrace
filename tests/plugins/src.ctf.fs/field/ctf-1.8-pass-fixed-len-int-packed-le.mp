---
struct {
  integer { size = 3; align = 1; byte_order = le; }                a;
  integer { size = 7; align = 1; byte_order = le; signed = true; } b;
  integer { size = 6; align = 1; byte_order = le; }                c;
  integer { size = 8; align = 1; byte_order = le; signed = true; } d;
}

---
[((-1 & 0xff) << 16) | (42 << 10) | ((-10 & 0x7f) << 3) | 5:24le]

---
a: 5
b: -10
c: 42
d: -1

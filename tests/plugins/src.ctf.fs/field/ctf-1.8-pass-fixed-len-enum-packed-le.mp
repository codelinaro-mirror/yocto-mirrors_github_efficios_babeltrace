---
struct {
  enum : integer { size = 3; align = 1; byte_order = le; }                { A, B, C }              a;
  enum : integer { size = 7; align = 1; byte_order = le; signed = true; } { A = -1, B = 0, C = 1 } b;
  enum : integer { size = 6; align = 1; byte_order = le; }                { A, B, C }              c;
  enum : integer { size = 8; align = 1; byte_order = le; signed = true; } { A = -1, B = 0, C = 1 } d;
}

---
[((-1 & 0xff) << 16) | (42 << 10) | ((-10 & 0x7f) << 3) | 5:24le]

---
a: 5
b: -10
c: 42
d: -1

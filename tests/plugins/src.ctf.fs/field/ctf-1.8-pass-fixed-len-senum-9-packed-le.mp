---
struct {
  enum : integer { size = 3; align = 1; byte_order = le; }                { A, B, C }              a;
  enum : integer { size = 9; align = 1; byte_order = le; signed = true; } { A = -1, B = 0, C = 1 } b;
  enum : integer { size = 4; align = 1; byte_order = le; }                { A, B, C }              c;
}

---
[(9 << 12) | ((-100 & 0x1ff) << 3) | 5 : 16le]

---
a: 5
b: -100
c: 9

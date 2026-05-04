---
struct {
  enum : integer { size = 3; align = 1; byte_order = be; }                { A, B, C }              a;
  enum : integer { size = 9; align = 1; byte_order = be; signed = true; } { A = -1, B = 0, C = 1 } b;
  enum : integer { size = 4; align = 1; byte_order = be; }                { A, B, C }              c;
}

---
[(5 << 13) | ((-100 & 0x1ff) << 4) | 9 : 16be]

---
a: 5
b: -100
c: 9

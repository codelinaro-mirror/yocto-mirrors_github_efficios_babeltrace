---
struct {
  enum : integer { size = 1; align = 1; byte_order = le; }                { A, B }          u;
  enum : integer { size = 1; align = 1; byte_order = le; signed = true; } { A = -1, B = 0 } s;
  enum : integer { size = 6; align = 1; byte_order = le; }                { A, B, C }       pad;
}

---
[(0 << 2) | (1 << 1) | 1 : 8]

---
u: 1
s: -1
pad: 0

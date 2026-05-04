---
struct {
  integer { size = 1; align = 1; byte_order = le; }                u;
  integer { size = 1; align = 1; byte_order = le; signed = true; } s;
  integer { size = 6; align = 1; byte_order = le; }                pad;
}

---
[(0 << 2) | (1 << 1) | 1 : 8]

---
u: 1
s: -1
pad: 0

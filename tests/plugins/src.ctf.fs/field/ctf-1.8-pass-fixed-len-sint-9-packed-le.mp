---
struct {
  integer { size = 3; align = 1; byte_order = le; }                a;
  integer { size = 9; align = 1; byte_order = le; signed = true; } b;
  integer { size = 4; align = 1; byte_order = le; }                c;
}

---
[(9 << 12) | ((-100 & 0x1ff) << 3) | 5 : 16le]

---
a: 5
b: -100
c: 9

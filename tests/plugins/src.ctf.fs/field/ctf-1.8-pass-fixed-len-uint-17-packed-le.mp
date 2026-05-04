---
struct {
  integer { size = 3;  align = 1; byte_order = le; } a;
  integer { size = 17; align = 1; byte_order = le; } b;
  integer { size = 4;  align = 1; byte_order = le; } c;
}

---
[(9 << 20) | (100000 << 3) | 5 : 24le]

---
a: 5
b: 100000
c: 9

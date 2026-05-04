---
struct {
  integer { size = 4; align = 1; byte_order = le; } a;
  integer { size = 4; align = 1; byte_order = le; } b;
}

---
[(12 << 4) | 3 : 8]

---
a: 3
b: 12

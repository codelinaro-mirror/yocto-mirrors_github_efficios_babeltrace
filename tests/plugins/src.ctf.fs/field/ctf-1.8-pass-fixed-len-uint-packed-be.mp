---
struct {
  integer { size = 4; align = 1; byte_order = be; } a;
  integer { size = 4; align = 1; byte_order = be; } b;
}

---
[(3 << 4) | 12 : 8]

---
a: 3
b: 12

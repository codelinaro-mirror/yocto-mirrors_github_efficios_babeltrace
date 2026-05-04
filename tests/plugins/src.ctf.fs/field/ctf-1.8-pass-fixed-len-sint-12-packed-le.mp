---
struct {
  integer { size = 12; align = 1; byte_order = le; signed = true; } a;
  integer { size = 12; align = 1; byte_order = le; signed = true; } b;
}

---
[((50 & 0xfff) << 12) | (-100 & 0xfff) : 24le]

---
a: -100
b: 50

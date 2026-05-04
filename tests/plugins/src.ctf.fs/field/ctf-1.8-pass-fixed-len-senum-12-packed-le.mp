---
struct {
  enum : integer { size = 12; align = 1; byte_order = le; signed = true; } { A = -1, B = 0, C = 1 } a;
  enum : integer { size = 12; align = 1; byte_order = le; signed = true; } { A = -1, B = 0, C = 1 } b;
}

---
[((50 & 0xfff) << 12) | (-100 & 0xfff) : 24le]

---
a: -100
b: 50

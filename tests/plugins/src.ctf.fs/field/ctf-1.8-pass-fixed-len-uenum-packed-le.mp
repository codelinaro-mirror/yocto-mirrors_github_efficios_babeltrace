---
struct {
  enum : integer { size = 4; align = 1; byte_order = le; } { A, B, C } a;
  enum : integer { size = 4; align = 1; byte_order = le; } { A, B, C } b;
}

---
[(12 << 4) | 3 : 8]

---
a: 3
b: 12

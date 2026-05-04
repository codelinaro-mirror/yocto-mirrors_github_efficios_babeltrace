---
struct {
  enum : integer { size = 3;  align = 1; byte_order = le; } { A, B, C } a;
  enum : integer { size = 17; align = 1; byte_order = le; } { A, B, C } b;
  enum : integer { size = 4;  align = 1; byte_order = le; } { A, B, C } c;
}

---
[(9 << 20) | (100000 << 3) | 5 : 24le]

---
a: 5
b: 100000
c: 9

---
struct {
  enum : integer { size = 4; align = 1; byte_order = be; } { A, B, C } a;
  enum : integer { size = 4; align = 1; byte_order = be; } { A, B, C } b;
}

---
[(3 << 4) | 12 : 8]

---
a: 3
b: 12

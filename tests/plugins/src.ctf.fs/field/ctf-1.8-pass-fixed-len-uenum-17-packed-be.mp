---
struct {
  enum : integer { size = 3;  align = 1; byte_order = be; } { A, B, C } a;
  enum : integer { size = 17; align = 1; byte_order = be; } { A, B, C } b;
  enum : integer { size = 4;  align = 1; byte_order = be; } { A, B, C } c;
}

---
[(5 << 21) | (100000 << 4) | 9 : 24be]

---
a: 5
b: 100000
c: 9

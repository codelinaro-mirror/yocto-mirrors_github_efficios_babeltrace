---
struct {
  enum : integer { size = 3; align = 1; byte_order = be; }                { A, B, C }               a;
  enum : integer { size = 7; align = 1; byte_order = be; signed = true; } { A = -1, B = 0, C = 1 }  b;
  enum : integer { size = 6; align = 1; byte_order = be; }                { A, B, C }               c;
  enum : integer { size = 8; align = 1; byte_order = be; signed = true; } { A = -1, B = 0, C = 1 }  d;
}

---
[(5 << 21) | ((-10 & 0x7f) << 14) | (42 << 8) | (-1 & 0xff) : 24be]

---
a: 5
b: -10
c: 42
d: -1

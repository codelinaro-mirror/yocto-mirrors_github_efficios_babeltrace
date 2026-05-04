---
struct {
  integer { size = 3;  align = 1; byte_order = be; } a;
  integer { size = 17; align = 1; byte_order = be; } b;
  integer { size = 4;  align = 1; byte_order = be; } c;
}

---
[(5 << 21) | (100000 << 4) | 9 : 24be]

---
a: 5
b: 100000
c: 9

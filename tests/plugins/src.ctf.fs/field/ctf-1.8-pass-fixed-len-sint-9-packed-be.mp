---
struct {
  integer { size = 3; align = 1; byte_order = be; }                a;
  integer { size = 9; align = 1; byte_order = be; signed = true; } b;
  integer { size = 4; align = 1; byte_order = be; }                c;
}

---
[(5 << 13) | ((-100 & 0x1ff) << 4) | 9 : 16be]

---
a: 5
b: -100
c: 9

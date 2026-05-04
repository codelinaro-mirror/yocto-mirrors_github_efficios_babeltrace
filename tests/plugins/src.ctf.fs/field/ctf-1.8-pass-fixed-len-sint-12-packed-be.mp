---
struct {
  integer { size = 12; align = 1; byte_order = be; signed = true; } a;
  integer { size = 12; align = 1; byte_order = be; signed = true; } b;
}

---
[((-100 & 0xfff) << 12) | (50 & 0xfff) : 24be]

---
a: -100
b: 50

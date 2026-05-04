---
struct {
  integer { size = 1; align = 1; byte_order = le; } a;
  integer { size = 1; align = 1; byte_order = le; } b;
  integer { size = 1; align = 1; byte_order = le; } c;
  integer { size = 1; align = 1; byte_order = le; } d;
  integer { size = 1; align = 1; byte_order = le; } e;
  integer { size = 1; align = 1; byte_order = le; } f;
  integer { size = 1; align = 1; byte_order = le; } g;
  integer { size = 1; align = 1; byte_order = le; } h;
}

---
%
  0   # `h` (bit 7, MSB)
  1   # `g`
  0   # `f`
  0   # `e`
  1   # `d`
  1   # `c`
  0   # `b`
  1   # `a` (bit 0, LSB)

---
a: 1
b: 0
c: 1
d: 1
e: 0
f: 0
g: 1
h: 0

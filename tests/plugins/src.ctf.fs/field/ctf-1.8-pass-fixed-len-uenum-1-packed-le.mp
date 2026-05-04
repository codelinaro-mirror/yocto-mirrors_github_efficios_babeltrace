---
struct {
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } a;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } b;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } c;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } d;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } e;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } f;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } g;
  enum : integer { size = 1; align = 1; byte_order = le; } { A, B } h;
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

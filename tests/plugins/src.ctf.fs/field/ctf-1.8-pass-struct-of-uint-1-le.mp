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
  integer { size = 1; align = 1; byte_order = le; } i;
  integer { size = 1; align = 1; byte_order = le; } j;
  integer { size = 1; align = 1; byte_order = le; } k;
  integer { size = 1; align = 1; byte_order = le; } l;
  integer { size = 1; align = 1; byte_order = le; } m;
  integer { size = 1; align = 1; byte_order = le; } n;
  integer { size = 1; align = 1; byte_order = le; } o;
  integer { size = 1; align = 1; byte_order = le; } p;
}

---
%
  # byte 0
  1   # `h` (bit 7, MSB)
  0   # `g`
  1   # `f`
  0   # `e`
  1   # `d`
  0   # `c`
  1   # `b`
  0   # `a` (bit 0, LSB)
%
  # byte 1
  1   # `p` (bit 7, MSB)
  1   # `o`
  0   # `n`
  0   # `m`
  1   # `l`
  1   # `k`
  0   # `j`
  0   # `i` (bit 0, LSB)

---
a: 0
b: 1
c: 0
d: 1
e: 0
f: 1
g: 0
h: 1
i: 0
j: 0
k: 1
l: 1
m: 0
n: 0
o: 1
p: 1

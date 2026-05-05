---
struct {
  integer { size = 1; align = 1; byte_order = be; } a;
  integer { size = 1; align = 1; byte_order = be; } b;
  integer { size = 1; align = 1; byte_order = be; } c;
  integer { size = 1; align = 1; byte_order = be; } d;
  integer { size = 1; align = 1; byte_order = be; } e;
  integer { size = 1; align = 1; byte_order = be; } f;
  integer { size = 1; align = 1; byte_order = be; } g;
  integer { size = 1; align = 1; byte_order = be; } h;
  integer { size = 1; align = 1; byte_order = be; } i;
  integer { size = 1; align = 1; byte_order = be; } j;
  integer { size = 1; align = 1; byte_order = be; } k;
  integer { size = 1; align = 1; byte_order = be; } l;
  integer { size = 1; align = 1; byte_order = be; } m;
  integer { size = 1; align = 1; byte_order = be; } n;
  integer { size = 1; align = 1; byte_order = be; } o;
  integer { size = 1; align = 1; byte_order = be; } p;
}

---
%
  # byte 0
  0   # `a` (bit 7, MSB)
  1   # `b`
  0   # `c`
  0   # `d`
  1   # `e`
  0   # `f`
  1   # `g`
  1   # `h` (bit 0, LSB)
%
  # byte 1
  1   # `i` (bit 7, MSB)
  1   # `j`
  0   # `k`
  0   # `l`
  1   # `m`
  1   # `n`
  0   # `o`
  0   # `p` (bit 0, LSB)

---
a: 0
b: 1
c: 0
d: 0
e: 1
f: 0
g: 1
h: 1
i: 1
j: 1
k: 0
l: 0
m: 1
n: 1
o: 0
p: 0

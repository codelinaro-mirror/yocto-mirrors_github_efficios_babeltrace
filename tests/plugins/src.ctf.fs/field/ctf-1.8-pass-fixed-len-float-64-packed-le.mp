---
struct {
  integer { size = 4; align = 1; byte_order = le; }                           a;
  floating_point { exp_dig = 11; mant_dig = 53; align = 1; byte_order = le; } f;
  integer { size = 4; align = 1; byte_order = le; }                           b;
}

---
# `a`: 5
# `f`: 0.5 (0x3fe0000000000000 as IEEE 754 binary64)
# `b`: 10
05 00 00 00 00 00 00 fe a3

---
a: 5
f: 0.500000
b: 10

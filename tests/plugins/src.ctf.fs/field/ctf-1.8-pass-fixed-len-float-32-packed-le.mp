---
struct {
  integer { size = 4; align = 1; byte_order = le; }                          a;
  floating_point { exp_dig = 8; mant_dig = 24; align = 1; byte_order = le; } f;
  integer { size = 4; align = 1; byte_order = le; }                          b;
}

---
# 1.5 is 0x3fc00000 (IEEE 754 binary32)
[(10 << 36) | (0x3fc00000 << 4) | 5 : 40le]

---
a: 5
f: 1.500000
b: 10

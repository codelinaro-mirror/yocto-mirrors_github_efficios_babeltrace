---
struct {
  integer { size = 4; align = 1; byte_order = be; }                          a;
  floating_point { exp_dig = 8; mant_dig = 24; align = 1; byte_order = be; } f;
  integer { size = 4; align = 1; byte_order = be; }                          b;
}

---
# 1.5 is 0x3fc00000 (IEEE 754 binary32)
[(5 << 36) | (0x3fc00000 << 4) | 10 : 40be]

---
a: 5
f: 1.500000
b: 10

---
struct {
  floating_point { exp_dig = 8; mant_dig = 24; byte_order = le; } little;
  floating_point { exp_dig = 8; mant_dig = 24; byte_order = be; } big;
}

---
[1.5:32le]  # `little`
[1.5:32be]  # `big`

---
little: 1.500000
big: 1.500000

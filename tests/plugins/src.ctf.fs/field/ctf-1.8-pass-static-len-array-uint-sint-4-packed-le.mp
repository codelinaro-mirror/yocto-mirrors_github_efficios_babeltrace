---
struct {
  integer {                size = 4; align = 1; byte_order = le; } arr_u[1];
  integer { signed = true; size = 4; align = 1; byte_order = le; } arr_s[1];
}

---
[((-3 & 0xf) << 4) | (10 & 0xf) : 8]

---
arr_u:
  - 10
arr_s:
  - -3

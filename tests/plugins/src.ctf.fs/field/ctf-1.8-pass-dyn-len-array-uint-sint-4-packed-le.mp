---
struct {
  u8                                                               len_u;
  u8                                                               len_s;
  integer {                size = 4; align = 1; byte_order = le; } arr_u[len_u];
  integer { signed = true; size = 4; align = 1; byte_order = le; } arr_s[len_s];
}

---
$1                                    # `len_u`
$1                                    # `len_s`
[((-3 & 0xf) << 4) | (10 & 0xf) : 8]  # `arr_u` (low nibble) + `arr_s` (high nibble)

---
len_u: 1
len_s: 1
arr_u:
  - 10
arr_s:
  - -3

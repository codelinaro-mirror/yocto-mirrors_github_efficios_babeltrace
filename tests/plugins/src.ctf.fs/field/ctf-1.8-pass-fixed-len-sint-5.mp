---
struct {
  integer { size = 5; signed = true; align = 1; byte_order = le; } a;
  integer { size = 3;                align = 1; byte_order = le; } pad;
}

---
[(0 << 5) | (-5 & 0x1f) : 8]

---
a: -5
pad: 0

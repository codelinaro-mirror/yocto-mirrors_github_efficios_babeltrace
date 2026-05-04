---
struct {
  enum : integer { size = 5; signed = true; align = 1; byte_order = le; } { A = -1, B = 0, C = 1 } a;
  enum : integer { size = 3;                align = 1; byte_order = le; } { A, B, C }              pad;
}

---
[(0 << 5) | (-5 & 0x1f) : 8]

---
a: -5
pad: 0

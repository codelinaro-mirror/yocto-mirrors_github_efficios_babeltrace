---
struct {
  enum : integer { size = 1; align = 1; byte_order = le; } {
    A,
    B,
  }                                                 sel;

  integer { size = 1; align = 1; byte_order = le; } a;

  variant <sel> {
    nt_str                                            A;
    integer { size = 1; align = 1; byte_order = le; } B;
  }                                                 var;

  integer { size = 1; align = 1; byte_order = le; } b;
  integer { size = 4; align = 1; byte_order = le; } pad;
}

---
%
  0000  # `pad` (bits 7..4)
  1     # `b`   (bit 3)
  1     # `var` (bit 2)
  0     # `a`   (bit 1)
  1     # `sel` (bit 0, LSB)

---
sel: 1
a: 0
var: 1
b: 1
pad: 0

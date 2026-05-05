---
struct {
  integer { size = 5; align = 1; byte_order = le; } pre;

  enum : integer { size = 2; align = 1; byte_order = le; } {
    A,
    B,
  }                                                 tag;

  variant <tag> {
    integer { size = 1; align = 1; byte_order = le; } A;
    integer { size = 1; align = 1; byte_order = le; } B;
  }                                                 var;
}

---
%
  1       # `var` (bit 7, MSB)
  00      # `tag`
  10110   # `pre` (LSBs)

---
pre: 22
tag: 0
var: 1

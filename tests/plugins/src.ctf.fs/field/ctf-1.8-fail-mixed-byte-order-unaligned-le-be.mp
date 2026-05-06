---
struct {
  integer { size = 5; align = 1; byte_order = le; } a;
  integer { size = 3; align = 1; byte_order = be; } b;
} @

---
ff

---
two contiguous fixed-length bit array fields which aren't byte-aligned don't share the same byte order: little-endian followed with big-endian

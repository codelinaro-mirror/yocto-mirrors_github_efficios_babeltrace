---
struct {
  integer { size = 5; align = 1; byte_order = be; } a;
  integer { size = 3; align = 1; byte_order = le; } b;
} @

---
ff

---
two contiguous fixed-length bit array fields which aren't byte-aligned don't share the same byte order: big-endian followed with little-endian

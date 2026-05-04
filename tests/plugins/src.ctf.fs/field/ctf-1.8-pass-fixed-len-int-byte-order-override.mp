---
struct {
  integer { size = 32; byte_order = le; } little;
  integer { size = 32; byte_order = be; } big;
}

---
[305419896:32le]  # `little`
[305419896:32be]  # `big`

---
little: 305419896
big: 305419896

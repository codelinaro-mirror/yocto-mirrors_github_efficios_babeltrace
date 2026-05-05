---
struct {
  u8 lead;

  struct {
    integer { size = 32; align = 32; byte_order = le; } x;
    u8                                                  y;
  }  s;
}

---
$1          # `lead`
@32         # 24 bits of padding because `s` inherits alignment of `s.x`
[42:32le]   # `s.x`
$5          # `s.y`

---
lead: 1
s:
  x: 42
  y: 5

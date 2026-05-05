---
struct {
  u8 before;

  enum : u8le {
    ONLY,
  }  tag;

  variant <tag> {
    integer { size = 32; align = 32; byte_order = le; } ONLY;
  }  var;

  u8 after;
}

---
ab                  # `before`
00                  # `tag`
@32                 # padding to 32-bit boundary (driven by inner 32-bit)
[3735928559:32le]   # `var`
$42                 # `after`

---
before: 171
tag: 0
var: 3735928559
after: 42

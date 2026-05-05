---
struct {
  enum : u8le {
    A,
    B,
  }  tag;

  variant <tag> {
    struct {} A;
    u8        B;
  }  var;

  u8 after;
} @[2]

---
# first element
00    # `tag`
$42   # `after`

# second element
01    # `tag`
$77   # `var`
$99   # `after`

---
- tag: 0
  var: ∅
  after: 42
- tag: 1
  var: 77
  after: 99

---
struct {
  enum : u8le {
    A,
    B,
  } tag;

  variant <tag> {
    u16le A[3];
    u8    B;
  } var;
} @[2]

---
# first element
00                        # `tag`
[10:16] [20:16] [30:16]   # `var` (array field of three `u16le`)

# second element
01              # `tag`
$42             # `var`

---
- tag: 0
  var:
    - 10
    - 20
    - 30
- tag: 1
  var: 42

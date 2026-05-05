---
struct {
  enum : u8le {
    A,
    B,
  } tag;

  variant <tag> {
    struct {
      u8    x;
      u16le y;
    } A;

    nt_str B;
  } var;
} @[2]

---
# first element
00          # `tag`
$10         # `var.x`
[2000:16]   # `var.y`

# second element
01          # `tag`
"bonjour\0" # `var`

---
- tag: 0
  var:
    x: 10
    y: 2000
- tag: 1
  var: "bonjour"

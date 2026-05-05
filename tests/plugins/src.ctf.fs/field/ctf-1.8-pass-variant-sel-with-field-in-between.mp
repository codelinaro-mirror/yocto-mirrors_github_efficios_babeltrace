---
struct {
  enum : u8le {
    A,
    B,
  } tag;

  u32le between;

  variant <tag> {
    u16le A;
    u8    B;
  } var;
}

---
00            # `tag`
[51966:32le]  # `between`
[1995:16]     # `var`

---
tag: 0
between: 51966
var: 1995

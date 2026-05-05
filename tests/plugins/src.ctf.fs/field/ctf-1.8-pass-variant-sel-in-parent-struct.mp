---
struct {
  enum : u8le {
    A,
    B,
  } tag;

  struct {
    variant <tag> {
      u16le A;
      u8    B;
    } var;
  } inner;
}

---
00          # `tag`
[1995:16]   # `inner.var`

---
tag: 0
inner:
  var: 1995

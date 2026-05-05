---
struct {
  enum : u8le {
    ONLY,
  } tag;

  variant <tag> {
    u32le ONLY;
  } var;
}

---
00                  # `tag`
[3735928559:32le]   # `var`

---
tag: 0
var: 3735928559

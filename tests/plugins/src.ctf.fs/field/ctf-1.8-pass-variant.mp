---
struct {
  enum : u8le {
    MEOW,
    MIX,
  } tag;

  variant <tag> {
    u16le  MEOW;
    nt_str MIX;
  } var;
} @[2]

---
# first element
00                # `tag`
[1995:16]         # `var`

# second element
01                # `tag`
"hello there!\0"  # `var`
---
- tag: 0
  var: 1995
- tag: 1
  var: "hello there!"

---
struct {
  enum : u8le {
    A,
    B,
  } outer_tag;

  enum : u8le {
    X,
    Y,
  } inner_tag;

  variant <outer_tag> {
    variant <inner_tag> {
      u8    X;
      u16le Y;
    } A;

    nt_str B;
  } var;
} @[3]

---
00          # `outer_tag`
00          # `inner_tag`
$77         # `var` (`u8`)

00          # `outer_tag`
01          # `inner_tag`
[2024:16]   # `var` (`u16le )

01          # `outer_tag`
00          # `inner_tag`
"yo!\0"     # `var` (`nt_str`)

---
- outer_tag: 0
  inner_tag: 0
  var: 77
- outer_tag: 0
  inner_tag: 1
  var: 2024
- outer_tag: 1
  inner_tag: 0
  var: "yo!"

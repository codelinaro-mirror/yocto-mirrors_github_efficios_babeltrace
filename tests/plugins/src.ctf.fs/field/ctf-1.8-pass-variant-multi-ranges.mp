---
struct {
  enum : u8 {
    STR = 1 ... 3,
    STR = 100 ... 200,
    INT = 10 ... 20,
    INT = 240 ... 255,
  } tag;

  variant <tag> {
    nt_str STR;
    u16le  INT;
  } var;
}

---
$150    # `tag`
"hi\0"  # `var`

---
tag: 150
var: "hi"

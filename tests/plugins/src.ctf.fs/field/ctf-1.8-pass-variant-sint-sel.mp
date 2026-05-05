---
struct {
  enum : i8 {
    NEG = -50 ... -10,
    POS = 0 ... 100,
  } tag;

  variant <tag> {
    nt_str NEG;
    u16le  POS;
  } var;
}

---
$-25        # `tag`
"chilly\0"  # `var`

---
tag: -25
var: "chilly"

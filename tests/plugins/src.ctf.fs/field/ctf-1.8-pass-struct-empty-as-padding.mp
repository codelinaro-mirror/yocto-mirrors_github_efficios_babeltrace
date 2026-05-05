---
struct {
  u8          a;

  struct {
  } align(64) pad;

  u32le       b;
}

---
$1                # `a`
@64               # 56 bits of padding inserted to honour alignment of `pad`
[12345678:32le]   # `b`

---
a: 1
pad: ∅
b: 12345678

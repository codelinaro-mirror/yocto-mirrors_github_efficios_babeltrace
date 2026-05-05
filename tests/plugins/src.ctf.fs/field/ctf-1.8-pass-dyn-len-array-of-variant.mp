---
struct {
  u8 len;

  enum : u8 {
    A,
    B,
  } tag;

  variant <tag> {
    u16le  A;
    nt_str B;
  } arr[len];
}

---
$3                            # `len`
00                            # `tag`
[1995:16] [42:16] [1234:16]   # `arr` (3 × `u16le`)

---
len: 3
tag: 0
arr:
  - 1995
  - 42
  - 1234

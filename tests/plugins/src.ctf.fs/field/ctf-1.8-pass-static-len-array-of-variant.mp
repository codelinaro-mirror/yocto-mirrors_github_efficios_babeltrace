---
struct {
  enum : u8 {
    A,
    B,
  } tag;

  variant <tag> {
    u16le  A;
    nt_str B;
  } arr[3];
}

---
00                            # `tag`
[1995:16] [42:16] [1234:16]   # `arr` (3 × `u16le`)

---
tag: 0
arr:
  - 1995
  - 42
  - 1234

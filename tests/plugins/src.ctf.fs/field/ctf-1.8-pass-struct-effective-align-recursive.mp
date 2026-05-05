---
struct {
  u8 lead;

  struct {
    struct {
      integer { size = 64; align = 64; byte_order = le; } z;
    }  inner;

    u8 q;
  }  outer;
}

---
$1                # `lead`
@64               # 56 bits of padding: `outer` inherits alignment of `outer.inner.z`
[123456789:64le]  # `outer.inner.z`
$7                # `outer.q`

---
lead: 1
outer:
  inner:
    z: 123456789
  q: 7

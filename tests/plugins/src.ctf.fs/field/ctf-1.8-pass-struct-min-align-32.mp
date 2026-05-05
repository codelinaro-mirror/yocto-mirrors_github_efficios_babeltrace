---
struct {
  u8          lead;

  struct {
    u8 a;
    u8 b;
  } align(32) aligned;
}

---
$5    # `lead`
@32   # 24 bits of padding before `aligned`
$10   # `aligned.a`
$20   # `aligned.b`

---
lead: 5
aligned:
  a: 10
  b: 20

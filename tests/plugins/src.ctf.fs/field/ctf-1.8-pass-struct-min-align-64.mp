---
struct {
  u8          lead;

  struct {
    u16le a;
    u16le b;
  } align(64) aligned;
}

---
$7          # `lead`
@64         # 56 bits of padding before `aligned`
[100:16le]  # `aligned.a`
[200:16le]  # `aligned.b`

---
lead: 7
aligned:
  a: 100
  b: 200

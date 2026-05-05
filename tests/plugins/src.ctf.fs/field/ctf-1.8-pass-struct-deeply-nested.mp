---
struct {
  struct {
    struct {
      struct {
        u8 v;
      } l3;
    } l2;
  } l1;
}

---
$42

---
l1:
  l2:
    l3:
      v: 42

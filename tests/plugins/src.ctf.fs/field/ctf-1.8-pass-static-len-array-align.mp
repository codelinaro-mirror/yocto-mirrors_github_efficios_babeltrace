---
struct {
  integer { size = 4;  align = 1;  byte_order = le; } pad;
  integer { size = 32; align = 32; byte_order = le; } arr[3];
}

---
[5:8le]                           # `pad` (low nibble) + 4 bits of padding
@32                               # 24 bits of padding
[100:32le] [200:32le] [300:32le]  # `arr`

---
pad: 5
arr:
  - 100
  - 200
  - 300

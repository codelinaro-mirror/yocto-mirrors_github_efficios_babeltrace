---
struct {
  integer { size = 4;  align = 1;  byte_order = le; } pad;
  u8                                                  len;
  integer { size = 32; align = 32; byte_order = le; } arr[len];
}

---
[5:8le]                           # `pad` (low nibble) + 4 bits of padding
$3                                # `len`
@32                               # 16 bits of padding
[100:32le] [200:32le] [300:32le]  # `arr`

---
pad: 5
len: 3
arr:
  - 100
  - 200
  - 300

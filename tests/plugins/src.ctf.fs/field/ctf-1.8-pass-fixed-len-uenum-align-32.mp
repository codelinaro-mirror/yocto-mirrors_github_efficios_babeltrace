---
struct {
  enum : u8le                                                { A, B, C } a;
  enum : integer { size = 32; byte_order = le; align = 32; } { A, B, C } b;
}

---
$1                  # `a`
12 34 45            # padding to 32-bit alignment for `b`
[2864434397:32le]   # `b`

---
a: 1
b: 2864434397

---
struct {
  u8     len;
  nt_str arr[len];
}

---
$3          # `len`
"hello\0"   # `arr[0]`
"world\0"   # `arr[1]`
"!\0"       # `arr[2]`

---
len: 3
arr:
  - "hello"
  - "world"
  - "!"

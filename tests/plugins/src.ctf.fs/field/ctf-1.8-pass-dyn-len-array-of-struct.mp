---
struct {
  u8 len;

  struct {
    u8le   a;
    nt_str b;
  }  arr[len];
}

---
$3            # `len`

01            # `a`
"salut\0"     # `b`

02            # `a`
"patente\0"   # `b`

03            # `a`
"Quebec\0"    # `b`

---
len: 3
arr:
  - a: 1
    b: "salut"
  - a: 2
    b: "patente"
  - a: 3
    b: "Quebec"

---
struct {
  enum : u8le {
    MEOW = 0,
    MIX = 1,
  } tag;

  variant <tag> {
    u8le  MEOW;
    u16le MIX;
  } var;
} @

---
05      # `tag` (no label maps to 5)
00 00

---
no variant field option selected by the selector value 5

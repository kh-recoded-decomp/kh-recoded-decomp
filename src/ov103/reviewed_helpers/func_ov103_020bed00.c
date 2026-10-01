#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bcd68();
extern u32 func_ov103_020c030c();

void func_ov103_020bed00(void) {
  int state;

  state = func_ov103_020c030c();
  if (state != 3) {
    return;
  }
  func_ov039_020bcd68(0xffffffff);
  func_ov039_020bbf78(0xffffffff,0xffffffff,1);
  func_0204d924(0,3);
}

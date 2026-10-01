#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bcd68();
extern u32 func_ov103_020c0180();
extern u32 func_ov103_020c030c();

void func_ov103_020beca4(u32 *work) {
  int ready;
  u32 selection;

  ready = func_ov103_020c030c();
  if (ready != 3) {
    return;
  }
  selection = *work;
  ready = func_ov103_020c0180(0,selection);
  if (ready == 0) {
    return;
  }
  func_0204d924(0,1);
  func_ov039_020bcd68(selection);
  func_ov039_020bbf78(0xffffffff,0xffffffff,1);
}

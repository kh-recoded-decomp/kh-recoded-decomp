#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc8a0();
extern u32 func_ov093_020c2348();

void func_ov093_020bf5ac(void) {
  int state;

  state = func_ov093_020c2348();
  if (state != 6) {
    return;
  }
  func_ov039_020bc8a0();
  func_ov039_020bbf78(0xb,0xffffffff,1);
  func_0204d924(0,3);
}

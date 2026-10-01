#include "nitro/types.h"

extern u32 func_02027304();
extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc8d0();

void func_ov077_020c5d98(int work) {
  int savedFlag;
  u32 nextMode;

  if ((*(int *)(work + 0x18) == 0) && (*(int *)(work + 0x7fb0) == 4)) {
    nextMode = 1;
    func_0204d924(1,3);
    savedFlag = func_02027304(0xf5b);
    if (savedFlag != 0) {
      nextMode = 2;
    }
    func_ov039_020bc8d0(nextMode);
    func_ov039_020bbf78(0,0xffffffff,1);
  }
}

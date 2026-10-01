#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov073_020c1d38();

void func_ov077_020c5f28(int work) {
  if ((*(int *)(work + 0x18) == 0) && (*(int *)(work + 0x7fb0) == 4)) {
    func_0204d924(1,2);
    func_ov073_020c1d38(0,0);
    func_ov039_020bbf78(1,0xffffffff,0);
  }
}

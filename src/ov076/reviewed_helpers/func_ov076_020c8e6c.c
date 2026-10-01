#include "nitro/types.h"

extern u32 PlaySoundEffect_0204d924();
extern u32 SlotMenu_CheckPointLimit_020c544c();
extern u32 func_ov039_020bbf78();
extern u32 func_ov073_020c1d38();

void func_ov076_020c8e6c(int *work) {
  int valid;

  if ((work[10] == 0) && (*work == 1)) {
    valid = SlotMenu_CheckPointLimit_020c544c(work,1);
    if (valid == 0) {
      PlaySoundEffect_0204d924(1,4);
      return;
    }
    PlaySoundEffect_0204d924(1,2);
    func_ov073_020c1d38(0,0);
    func_ov039_020bbf78(1,0xffffffff,0);
  }
}

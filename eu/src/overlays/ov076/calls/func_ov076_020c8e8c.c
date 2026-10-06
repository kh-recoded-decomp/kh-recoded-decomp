#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 SlotMenu_CheckPointLimit();
extern u32 StartSubScene();
extern u32 SetStatusHeaderText();

void func_ov076_020c8e8c(int *work) {
  int valid;

  if ((work[10] == 0) && (*work == 1)) {
    valid = SlotMenu_CheckPointLimit(work,1);
    if (valid == 0) {
      PlaySoundEffect(1,4);
      return;
    }
    PlaySoundEffect(1,2);
    SetStatusHeaderText(0,0);
    StartSubScene(1,0xffffffff,0);
  }
}

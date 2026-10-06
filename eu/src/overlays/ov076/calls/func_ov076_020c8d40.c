#include "nitro/types.h"

extern u32 IsGlobalPackedBitSet();
extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 ReplaceStackTop();
extern u32 SlotMenu_CheckPointLimit();

void func_ov076_020c8d40(int *work) {
  int result;

  if ((work[10] == 0) && (*work == 1)) {
    result = SlotMenu_CheckPointLimit(work,1);
    if (result == 0) {
      PlaySoundEffect(1,4);
      return;
    }
    PlaySoundEffect(1,3);
    result = IsGlobalPackedBitSet(0xf5b);
    ReplaceStackTop(result != 0);
    StartSubScene(0,0xffffffff,1);
  }
}

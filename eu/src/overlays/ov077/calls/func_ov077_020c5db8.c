#include "nitro/types.h"

extern u32 IsGlobalPackedBitSet();
extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 ReplaceStackTop();

void func_ov077_020c5db8(int work) {
  int savedFlag;
  u32 nextMode;

  if ((*(int *)(work + 0x18) == 0) && (*(int *)(work + 0x7fb0) == 4)) {
    nextMode = 1;
    PlaySoundEffect(1,3);
    savedFlag = IsGlobalPackedBitSet(0xf5b);
    if (savedFlag != 0) {
      nextMode = 2;
    }
    ReplaceStackTop(nextMode);
    StartSubScene(0,0xffffffff,1);
  }
}

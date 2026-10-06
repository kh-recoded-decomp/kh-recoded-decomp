#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();

void func_ov081_020c5a78(void) {
  PlaySoundEffect(0,3);
  PopStackEntry();
  StartSubScene(0,0xffffffff,1);
}

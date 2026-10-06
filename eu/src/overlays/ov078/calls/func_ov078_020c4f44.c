#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();

void func_ov078_020c4f44(void) {
  PlaySoundEffect(0,3);
  PopStackEntry();
  StartSubScene(0,0xffffffff,0);
}

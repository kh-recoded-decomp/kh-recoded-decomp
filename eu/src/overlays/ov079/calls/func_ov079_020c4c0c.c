#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();
extern u32 ConfigMenu_SaveOptions();

void func_ov079_020c4c0c(u32 work) {
  PlaySoundEffect(0,3);
  ConfigMenu_SaveOptions(work);
  PopStackEntry();
  StartSubScene(0,0xffffffff,0);
}

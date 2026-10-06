#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();
extern u32 func_ov093_020c2368();

void func_ov093_020bf600(void) {
  int state;

  state = func_ov093_020c2368();
  if (state != 6) {
    return;
  }
  PopStackEntry();
  PopStackEntry();
  StartSubScene(0,0xffffffff,1);
  PlaySoundEffect(0,3);
}

#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();

void ListScene_ReturnToParentMenu(void) {
  PopStackEntry();
  StartSubScene(0xb,0xffffffff,1);
  PlaySoundEffect(0,3);
}

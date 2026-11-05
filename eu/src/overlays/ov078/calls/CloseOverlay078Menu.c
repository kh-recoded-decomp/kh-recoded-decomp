#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();

void CloseOverlay078Menu(void) {
  PlaySoundEffect(0,3);
  PopStackEntry();
  StartSubScene(0,0xffffffff,0);
}

#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();
extern u32 TrophyReport_GetState();

void TrophyReport_ReturnToRootMenu(void) {
  int state;

  state = TrophyReport_GetState();
  if (state != 6) {
    return;
  }
  PopStackEntry();
  PopStackEntry();
  StartSubScene(0,0xffffffff,1);
  PlaySoundEffect(0,3);
}

#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 SetStatusHeaderText();

void ItemScreen_OpenMatrixMenu(int work) {
  if ((*(int *)(work + 0x18) == 0) && (*(int *)(work + 0x7fb0) == 4)) {
    PlaySoundEffect(1,2);
    SetStatusHeaderText(0,0);
    StartSubScene(1,0xffffffff,0);
  }
}

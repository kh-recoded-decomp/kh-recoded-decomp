#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 WriteSessionPackedBits();
extern u32 StartSubScene();
extern u32 func_ov039_020bc638();

void func_ov089_020c047c(void) {
  int selection;

  selection = func_ov039_020bc638();
  selection = *(int *)(*(int *)(selection + 0x748) * 0xc + *(int *)(selection + 0x738) + 8);
  if ((selection < 0) || (selection == 8)) {
    selection = 7;
  }
  else {
    selection = selection + 1;
  }
  WriteSessionPackedBits(0x3703,3,selection);
  PlaySoundEffect(0,1);
  StartSubScene(0xffffffff,0xffffffff,1);
}

#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 PlaySoundEffect();

void func_ov036_020c2814(void) {
  if (*(int *)(gTextWindowResourceTable + 0x68a4) != 0) {
    return;
  }
  PlaySoundEffect(0,7);
  *(u32 *)(gTextWindowResourceTable + 0x68a4) = 2;
}

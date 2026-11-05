#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 PlaySoundEffect();

void PlayTextWindowSound7WithCooldown(void) {
  if (*(int *)(gTextWindowResourceTable + 0x68a4) != 0) {
    return;
  }
  PlaySoundEffect(0,7);
  *(u32 *)(gTextWindowResourceTable + 0x68a4) = 2;
}

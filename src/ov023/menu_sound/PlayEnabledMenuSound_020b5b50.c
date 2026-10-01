#include "nitro/types.h"

extern u32 _data_ov023_020b6f64;
extern u32 PlaySoundEffect_0204d924();

void PlayEnabledMenuSound_020b5b50(void)

{
  if (*(int *)(_data_ov023_020b6f64 + 0x40) != 0) {
    PlaySoundEffect_0204d924(0,0x4a);
  }
  return;
}

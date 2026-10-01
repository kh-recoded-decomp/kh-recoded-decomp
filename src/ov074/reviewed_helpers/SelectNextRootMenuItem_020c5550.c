#include "nitro/types.h"

extern u16 _data_02060500;
extern u32 PlaySoundEffect_0204d924();

void SelectNextRootMenuItem_020c5550(u8 *context)

{
  int previousSelection;
  
  if (context[3] != 0) {
    return;
  }
  if (++*context >= context[1]) {
    if ((_data_02060500 & 0x80) == 0) {
      *context = context[1] - 1;
      return;
    }
    *context = 0;
  }
  PlaySoundEffect_0204d924(0,0);
  context[2] = 1;
  return;
}

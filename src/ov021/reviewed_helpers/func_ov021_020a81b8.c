#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int StopSoundSeqHandle_0204dbe4();

unsigned int func_ov021_020a81b8(int work,unsigned int value,unsigned int *resultSlot) {
  unsigned int result;

  if (*(u32 **)(work + 0x24) != (u32 *)0x0) {
    StopSoundSeqHandle_0204dbe4(**(u32 **)(work + 0x24));
  }
  result = (**(code **)(work + 0x14))
                    ((int)*(char *)(work + 0x1c),*(unsigned int *)(work + 0x28),value,0);
  *resultSlot = result;
  *(unsigned int **)(work + 0x24) = resultSlot;
  return 1;
}

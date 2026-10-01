#include "nitro/types.h"

extern u32 SetPackedStateLowBit_02084774();

u32 func_ov001_02084690(void *actor) {
  SetPackedStateLowBit_02084774(actor,1);
  *(u8 *)((int)actor + 0x82) = 1;
  return 0;
}

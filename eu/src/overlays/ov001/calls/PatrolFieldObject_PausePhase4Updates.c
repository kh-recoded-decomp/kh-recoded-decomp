#include "nitro/types.h"

extern u32 SetPackedStateLowBit();

u32 PatrolFieldObject_PausePhase4Updates(void *actor) {
  SetPackedStateLowBit(actor,1);
  *(u8 *)((int)actor + 0x82) = 1;
  return 0;
}

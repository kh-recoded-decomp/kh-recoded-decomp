#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern u32 ActorSlot_SetFlag8ByIndex();

void func_ov041_020c3678(int actorIndex) {
  int actor;

  actor = *(int *)(*(int *)(data_ov035_020bc4e0 + 0xb8) + 0x14) + actorIndex * 0x4b4;
  ActorSlot_SetFlag8ByIndex((u32)*(u8 *)(actor + 0x32c),0);
  *(u16 *)(actor + 0xdc) = 0;
  *(u16 *)(actor + 0xe0) = 0;
  *(u8 *)(actor + 4) = 6;
  *(u8 *)(actor + 6) = 3;
}

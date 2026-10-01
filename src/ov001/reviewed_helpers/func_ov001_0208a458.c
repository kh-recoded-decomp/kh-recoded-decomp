#include "nitro/types.h"

extern u32 ActorObject_ClearExtraSlot_0208aa80();
extern u32 Actor_SetVelocity_0208a268();

void func_ov001_0208a458(void *actor) {
  int index;

  index = 0;
  Actor_SetVelocity_0208a268(actor,(void *)0x0);
  *(u32 *)((int)actor + 0x858) = 0;
  *(u32 *)((int)actor + 0x848) = 0;
  *(u32 *)((int)actor + 0x844) = 0;
  *(u32 *)((int)actor + 0x840) = 0;
  do {
    ActorObject_ClearExtraSlot_0208aa80(actor,index);
    index = index + 1;
  } while (index < 3);
}

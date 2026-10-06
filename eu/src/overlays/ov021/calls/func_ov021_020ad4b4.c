#include "nitro/types.h"

extern u32 ResetObjectSlots();

void func_ov021_020ad4b4(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    ResetObjectSlots(actor,owner);
  }
}

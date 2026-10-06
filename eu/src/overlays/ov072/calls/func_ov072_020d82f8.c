#include "nitro/types.h"

extern u32 StopLoopingSounds();

void func_ov072_020d82f8(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    StopLoopingSounds(actor,owner);
  }
}

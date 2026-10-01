#include "nitro/types.h"

extern u32 StopLoopingSounds_020d8234();

void func_ov072_020d82d8(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    StopLoopingSounds_020d8234(actor,owner);
  }
}

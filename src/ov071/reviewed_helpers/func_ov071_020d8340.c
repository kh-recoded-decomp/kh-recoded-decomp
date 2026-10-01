#include "nitro/types.h"

extern u32 StopLoopingSounds_020d8270();

void func_ov071_020d8340(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    StopLoopingSounds_020d8270(actor,owner);
  }
}

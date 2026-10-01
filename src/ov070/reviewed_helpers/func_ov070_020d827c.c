#include "nitro/types.h"

extern u32 StopLoopingSounds_020d8210();

void func_ov070_020d827c(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    StopLoopingSounds_020d8210(actor,owner);
  }
}

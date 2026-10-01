#include "nitro/types.h"

extern u32 StopLoopingSounds_020ad470();

void func_ov021_020ad494(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    StopLoopingSounds_020ad470(actor,owner);
  }
}

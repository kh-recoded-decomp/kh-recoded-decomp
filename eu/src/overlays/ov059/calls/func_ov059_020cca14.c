#include "nitro/types.h"

extern u32 Actor_PlayAnimation();

void func_ov059_020cca14(void *actor,void *animation,int track,int frame,int blend) {
  Actor_PlayAnimation(actor,animation,track,frame,blend);
  *(u32 *)((int)actor + 0x75c) = 0x12;
  *(u32 *)((int)actor + 0x768) = 0;
}

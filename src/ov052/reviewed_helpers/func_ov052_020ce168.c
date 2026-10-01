#include "nitro/types.h"

extern u32 SetBlendTableAndBlendTrack_020cbf58();

void func_ov052_020ce168(void *actor,void *blendTable,int track,int frame,int blend) {
  SetBlendTableAndBlendTrack_020cbf58(actor,blendTable,track,frame,blend);
  *(u32 *)((int)actor + 0x75c) = 0xffffffff;
  *(u32 *)((int)actor + 0x768) = 0;
}

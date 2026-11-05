#include "nitro/types.h"

extern u32 SetBlendTableAndBlendTrack();

void BlendActorTrackAndClearActionId(void *actor,void *blendTable,int track,int frame,int blend) {
  SetBlendTableAndBlendTrack(actor,blendTable,track,frame,blend);
  *(u32 *)((int)actor + 0x75c) = 0xffffffff;
  *(u32 *)((int)actor + 0x768) = 0;
}

#include "nitro/types.h"

extern u32 CallVirtualHandlerSlot1_02001574();

void ResetSubtitleLine_020a8a50(void *stream)

{
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x50) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
  CallVirtualHandlerSlot1_02001574(stream,0);
  return;
}

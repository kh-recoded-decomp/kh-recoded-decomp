#include "nitro/types.h"

extern struct { int reserved; int context; } fieldState_020a04a4;
#define activeManager fieldState_020a04a4.context
extern u32 FillBackgroundLayerRect_02001a60();
extern u32 FlushBufferAndRunCallback_0200153c();
extern u32 SelectListNodeOrFirst_020019b8();
extern u32 UpdateWidgetLayerDefault_020b9df0();
extern u32 func_ov001_0206ea08();
extern u32 func_ov001_0207123c();
extern u32 func_ov027_020b9e00();

void DrawFieldMessageById_0206ff10(int messageId)

{
  int manager;
  int layerOwner;
  void *tileBuffer;
  int entryIndex;
  
  manager = activeManager;
  layerOwner = func_ov001_0207123c();
  tileBuffer = (void *)func_ov001_0206ea08(0xb);
  entryIndex = 0;
  do {
    if (messageId == *(int *)(manager + entryIndex * 8 + 0xe0)) {
      SelectListNodeOrFirst_020019b8
                ((void *)(manager + 0xa8),*(void **)(manager + entryIndex * 8 + 0xdc));
      FlushBufferAndRunCallback_0200153c((void *)(manager + 0xa8));
      break;
    }
    entryIndex = entryIndex + 1;
  } while (entryIndex < 0x16);
  if (entryIndex < 0x16) {
    if (tileBuffer == (void *)0x0) {
      tileBuffer = (void *)UpdateWidgetLayerDefault_020b9df0(layerOwner,0xb);
      FillBackgroundLayerRect_02001a60((void *)(manager + 0xa8),tileBuffer,0x16,0,'\x0f');
      func_ov027_020b9e00(layerOwner,0xb);
      return;
    }
    FillBackgroundLayerRect_02001a60((void *)(manager + 0xa8),tileBuffer,0x16,0,'\x0f');
  }
  return;
}

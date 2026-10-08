#pragma optimization_level 2
#include "nitro/types.h"

extern unsigned int data_ov023_020b6e94;
extern unsigned int GetFieldFont3();
extern unsigned int InitTextLayerAtFromEnd();
extern unsigned int func_ov027_020b9e10();
extern unsigned int func_ov001_0207123c();
extern unsigned int MarkTileTableRowDirty();

void func_ov023_020b5944
               (int work,unsigned int arg2,unsigned int arg3,unsigned int frameExtra) {
  u16 value;
  void *screenBase;
  void *font;
  int layerManager;
  u16 *destination;
  u16 *source;
  u16 frame [8];
  unsigned int savedFrameExtra;

  source = (u16 *)&data_ov023_020b6e94;
  destination = frame;
  layerManager = 8;
  savedFrameExtra = frameExtra;
  do {
    value = *source;
    source = source + 1;
    *destination = value;
    destination = destination + 1;
    layerManager = layerManager + -1;
  } while (layerManager != 0);
  layerManager = func_ov001_0207123c();
  screenBase = (void *)func_ov027_020b9e10(layerManager,0x1a);
  font = GetFieldFont3();
  InitTextLayerAtFromEnd((void *)(work + 0xc),6,screenBase,font,frame);
  MarkTileTableRowDirty(layerManager,0x1a);
  *(unsigned int *)(work + 8) = 1;
}

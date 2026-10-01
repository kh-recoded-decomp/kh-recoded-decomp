#pragma optimization_level 2
#include "nitro/types.h"

extern unsigned int data_ov023_020b6e74;
extern unsigned int GetFieldFont3_020711e0();
extern unsigned int InitTextLayerAtFromEnd_020014d0();
extern unsigned int UpdateWidgetLayerDefault_020b9df0();
extern unsigned int func_ov001_0207123c();
extern unsigned int func_ov027_020b9e00();

void func_ov023_020b5924
               (int work,unsigned int arg2,unsigned int arg3,unsigned int frameExtra) {
  u16 value;
  void *screenBase;
  void *font;
  int layerManager;
  u16 *destination;
  u16 *source;
  u16 frame [8];
  unsigned int savedFrameExtra;

  source = (u16 *)&data_ov023_020b6e74;
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
  screenBase = (void *)UpdateWidgetLayerDefault_020b9df0(layerManager,0x1a);
  font = GetFieldFont3_020711e0();
  InitTextLayerAtFromEnd_020014d0((void *)(work + 0xc),6,screenBase,font,frame);
  func_ov027_020b9e00(layerManager,0x1a);
  *(unsigned int *)(work + 8) = 1;
}

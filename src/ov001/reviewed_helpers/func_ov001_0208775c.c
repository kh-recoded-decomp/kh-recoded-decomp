#include "nitro/types.h"

extern unsigned int data_ov001_0209f2c8;
extern unsigned int GetStageObjectHandle_0209c0c4();

u16 func_ov001_0208775c(int objectIndex,u32 entryIndex) {
  void *object;

  if ((data_ov001_0209f2c8 != -1) &&
     (object = GetStageObjectHandle_0209c0c4(objectIndex + 1U & 0xffff), object != (void *)0x0)) {
    if (entryIndex >= (((int)*(short *)((int)object + 0xc) - (int)*(short *)((int)object + 10) + 1U) & 0xffff)) {
      return 0;
    }
    return *(short *)((int)object + entryIndex * 2 + 10) + 1;
  }
  return 0;
}

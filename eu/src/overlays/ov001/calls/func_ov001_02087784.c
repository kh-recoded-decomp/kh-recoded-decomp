#include "nitro/types.h"

extern unsigned int data_ov001_0209f2e8;
extern unsigned int GetStageObjectHandle();

u16 func_ov001_02087784(int objectIndex,u32 entryIndex) {
  void *object;

  if ((data_ov001_0209f2e8 != -1) &&
     (object = GetStageObjectHandle(objectIndex + 1U & 0xffff), object != (void *)0x0)) {
    if (entryIndex >= (((int)*(short *)((int)object + 0xc) - (int)*(short *)((int)object + 10) + 1U) & 0xffff)) {
      return 0;
    }
    return *(short *)((int)object + entryIndex * 2 + 10) + 1;
  }
  return 0;
}

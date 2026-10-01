#include "nitro/types.h"

extern u32 GetStageObjectHandle_0209c0c4();

void func_ov001_0209c744(int objectIndex,u32 value) {
  void *object;

  object = GetStageObjectHandle_0209c0c4(objectIndex + 1U & 0xffff);
  *(u32 *)((int)object + 0x18) = value;
}

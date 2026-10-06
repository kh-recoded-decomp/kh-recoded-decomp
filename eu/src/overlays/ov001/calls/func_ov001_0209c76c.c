#include "nitro/types.h"

extern u32 GetStageObjectHandle();

void func_ov001_0209c76c(int objectIndex,u32 value) {
  void *object;

  object = GetStageObjectHandle(objectIndex + 1U & 0xffff);
  *(u32 *)((int)object + 0x18) = value;
}

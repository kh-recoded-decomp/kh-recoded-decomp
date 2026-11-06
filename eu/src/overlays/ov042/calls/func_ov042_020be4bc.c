#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

void func_ov042_020be4bc(u32 value) {
  *(u32 *)(gCameraSceneGlobalStorage + 0x144) = value;
}

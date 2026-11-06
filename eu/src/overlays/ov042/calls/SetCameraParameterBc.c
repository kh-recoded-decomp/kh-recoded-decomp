#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

void SetCameraParameterBc(u32 value) {
  *(u32 *)(gCameraSceneGlobalStorage + 0x13c) = 0x7fffffff;
  *(u32 *)(gCameraSceneGlobalStorage + 0xbc) = value;
}

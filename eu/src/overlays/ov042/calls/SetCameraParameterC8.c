#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

void SetCameraParameterC8(u32 value) {
  *(u32 *)(gCameraSceneGlobalStorage + 0x13c) = 0x7fffffff;
  *(u32 *)(gCameraSceneGlobalStorage + 200) = value;
}

#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

void SetCameraHorizontalFollowBounds(u32 firstValue,int secondValue) {
  if ((*(int *)(gCameraSceneGlobalStorage + 200) != 0x7fffffff) && (secondValue == 0x7fffffff)) {
    *(u32 *)(gCameraSceneGlobalStorage + 0xd4) = 0;
    *(u32 *)(gCameraSceneGlobalStorage + 0xd0) = *(u32 *)(gCameraSceneGlobalStorage + 0x70);
  }
  *(u32 *)(gCameraSceneGlobalStorage + 0xc4) = firstValue;
  *(int *)(gCameraSceneGlobalStorage + 200) = secondValue;
  if (secondValue != 0x7fffffff) {
    *(u32 *)(gCameraSceneGlobalStorage + 0x140) = *(u32 *)(gCameraSceneGlobalStorage + 0x140) | 1;
    *(u32 *)(gCameraSceneGlobalStorage + 0xcc) = *(u32 *)(gCameraSceneGlobalStorage + 0x70);
  }
  *(u32 *)(gCameraSceneGlobalStorage + 0x13c) = 0x7fffffff;
}

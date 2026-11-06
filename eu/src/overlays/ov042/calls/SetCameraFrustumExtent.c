#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;
extern u32 FX_Mul();
extern u32 BuildCameraFrustumColliders();

void SetCameraFrustumExtent(int extent) {
  int work;
  u32 scaledExtent;

  work = gCameraSceneGlobalStorage;
  if (extent < 0x1000) {
    extent = 0x1000;
  }
  *(int *)(gCameraSceneGlobalStorage + 0x5c) = extent;
  *(int *)(work + 0x60) = -extent;
  *(int *)(work + 0x54) = -extent;
  *(int *)(work + 0x58) = extent;
  scaledExtent = FX_Mul(extent,*(u32 *)(work + 8));
  *(u32 *)(work + 0x58) = scaledExtent;
  scaledExtent = FX_Mul(*(u32 *)(work + 0x54),*(u32 *)(work + 8));
  *(u32 *)(work + 0x54) = scaledExtent;
  BuildCameraFrustumColliders();
}

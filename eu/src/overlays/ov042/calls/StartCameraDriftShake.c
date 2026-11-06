#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;
extern u32 InitDriftParticle();
extern u32 GetOv030SceneReferenceAxis();

void StartCameraDriftShake(u32 first,u32 second) {
  u32 context;

  *(u32 *)(gCameraSceneGlobalStorage + 0x38) = *(u32 *)(gCameraSceneGlobalStorage + 0x38) & 0xffff7fff;
  *(u32 *)(gCameraSceneGlobalStorage + 0x38) = *(u32 *)(gCameraSceneGlobalStorage + 0x38) | 0x10000;
  context = GetOv030SceneReferenceAxis();
  InitDriftParticle(gCameraSceneGlobalStorage + 0x148,context,first,second);
}

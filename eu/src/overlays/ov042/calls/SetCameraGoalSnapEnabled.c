#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

void SetCameraGoalSnapEnabled(u32 value) {
  *(u32 *)(gCameraSceneGlobalStorage + 0x144) = value;
}

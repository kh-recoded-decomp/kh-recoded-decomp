#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

u32 IsCameraShakeActive(void) {
  if (*(int *)(gCameraSceneGlobalStorage + 0x148) != 0) {
    return 1;
  }
  return 0;
}

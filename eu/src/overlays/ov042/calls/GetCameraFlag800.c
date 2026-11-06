#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

u32 GetCameraFlag800(void) {
  if (gCameraSceneGlobalStorage != 0) {
    return *(u32 *)(gCameraSceneGlobalStorage + 0x38) & 0x800;
  }
  return 0;
}

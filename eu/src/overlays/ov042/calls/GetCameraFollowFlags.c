#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;

u32 GetCameraFollowFlags(void) {
  return *(u32 *)(gCameraSceneGlobalStorage + 0x140);
}

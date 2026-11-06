#include "nitro/types.h"

extern u32 *gFieldTargetSelectionWork;

u32 GetTargetSelectionFadeLevel2(void) {
  if (gFieldTargetSelectionWork == (u32 *)0x0) {
    return 0x7fffffff;
  }
  if ((*gFieldTargetSelectionWork & 4) != 0) {
    return 0x7fffffff;
  }
  return gFieldTargetSelectionWork[0xd];
}

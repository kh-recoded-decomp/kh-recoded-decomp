#include "nitro/types.h"

extern u32 *gFieldTargetSelectionWork;

u32 GetTargetSelectionFlag2(void) {
  if (gFieldTargetSelectionWork == (u32 *)0x0) {
    return 0;
  }
  return *gFieldTargetSelectionWork & 2;
}

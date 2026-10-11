#include "nitro/types.h"

extern u32 *gStageManager;

u32 func_ov001_0209c5ac(u32 mask) {
  if (gStageManager != (u32 *)0x0) {
    return mask & *gStageManager;
  }
  return 0;
}

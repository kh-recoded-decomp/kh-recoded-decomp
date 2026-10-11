#include "nitro/types.h"

extern u32 *gStageManager;

void func_ov001_0209c5c4(u32 mask) {
  if (gStageManager != (u32 *)0x0) {
    *gStageManager = mask | *gStageManager;
  }
}

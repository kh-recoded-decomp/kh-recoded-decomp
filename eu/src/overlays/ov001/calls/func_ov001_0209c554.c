#include "nitro/types.h"

extern u32 *gStageManager;

void func_ov001_0209c554(void) {
  if (gStageManager != (u32 *)0x0) {
    *gStageManager = *gStageManager | 0x40000000;
  }
}

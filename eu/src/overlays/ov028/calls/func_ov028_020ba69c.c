#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern u32 PushVramState();
extern u32 func_ov001_02063620();

u32 func_ov028_020ba69c(void) {
  u32 busy;

  busy = func_ov001_02063620();
  if (busy == 0) {
    PushVramState();
    *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x8000;
    return 1;
  }
  return 0xffffffff;
}

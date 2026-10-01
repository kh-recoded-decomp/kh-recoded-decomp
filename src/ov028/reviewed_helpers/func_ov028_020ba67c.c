#include "nitro/types.h"

extern u32 data_ov028_020bb380;
extern u32 PushVramState_020365a4();
extern u32 func_ov001_02063620();

u32 func_ov028_020ba67c(void) {
  u32 busy;

  busy = func_ov001_02063620();
  if (busy == 0) {
    PushVramState_020365a4();
    *(u16 *)(data_ov028_020bb380 + 6) = *(u16 *)(data_ov028_020bb380 + 6) | 0x8000;
    return 1;
  }
  return 0xffffffff;
}

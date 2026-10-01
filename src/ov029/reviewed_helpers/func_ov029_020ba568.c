#include "nitro/types.h"

extern u32 data_ov029_020baba0;
extern u32 PushVramState_020365a4();
extern u32 func_ov001_02063620();

u32 func_ov029_020ba568(void) {
  u32 busy;

  busy = func_ov001_02063620();
  if (busy == 0) {
    PushVramState_020365a4();
    *(u16 *)(data_ov029_020baba0 + 6) = *(u16 *)(data_ov029_020baba0 + 6) | 0x8000;
    return 1;
  }
  return 0xffffffff;
}

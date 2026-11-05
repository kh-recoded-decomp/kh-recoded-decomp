#include "nitro/types.h"

extern u32 data_ov001_020a0494;

void ResumeSessionTimerUpdates(void) {
  *(u8 *)(data_ov001_020a0494 + 0x24) = 1;
}

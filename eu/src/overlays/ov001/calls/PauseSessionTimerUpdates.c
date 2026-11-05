#include "nitro/types.h"

extern u32 data_ov001_020a0494;

void PauseSessionTimerUpdates(void) {
  *(u8 *)(data_ov001_020a0494 + 0x24) = 0;
}

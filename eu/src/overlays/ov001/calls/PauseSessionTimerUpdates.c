#include "nitro/types.h"

extern u32 gSessionTimerWork;

void PauseSessionTimerUpdates(void) {
  *(u8 *)(gSessionTimerWork + 0x24) = 0;
}

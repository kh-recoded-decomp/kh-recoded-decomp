#include "nitro/types.h"

extern u32 gSessionTimerWork;

void ResumeSessionTimerUpdates(void) {
  *(u8 *)(gSessionTimerWork + 0x24) = 1;
}

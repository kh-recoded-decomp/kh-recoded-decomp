#include "nitro/types.h"

extern u32 SetSessionStateBit();
extern u32 SetPostIntroElapsedMilliseconds();

void StartPostIntroElapsedTimer(void) {
  SetPostIntroElapsedMilliseconds(0);
  SetSessionStateBit(1,2);
}

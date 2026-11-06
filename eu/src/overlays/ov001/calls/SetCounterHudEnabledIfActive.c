#include "nitro/types.h"

extern int *gCounterHudWork;

int SetCounterHudEnabledIfActive(int value) {
  if ((gCounterHudWork != (int *)0x0) && (*gCounterHudWork != 0)) {
    gCounterHudWork[0x3c] = value;
    return 1;
  }
  return 0;
}

#include "nitro/types.h"

extern int *gCounterHudWork;

int AccumulateCounterHudDelta(int delta) {
  if ((gCounterHudWork != (int *)0x0) &&
     (((*gCounterHudWork == 1 || (*gCounterHudWork == 3)) && (delta != 0)))) {
    if (gCounterHudWork[1] != 2) {
      gCounterHudWork[0x47] = gCounterHudWork[0x47] + delta;
    }
    return 1;
  }
  return 0;
}

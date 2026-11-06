#include "nitro/types.h"

extern unsigned int *gMessageWindowWork;

void func_ov001_0207a880(int value) {
  unsigned int *work;

  work = gMessageWindowWork;
  gMessageWindowWork[0x3e] = value;
  *work = 0;
  if (value != 0) {
    work[3] = 0;
  }
}

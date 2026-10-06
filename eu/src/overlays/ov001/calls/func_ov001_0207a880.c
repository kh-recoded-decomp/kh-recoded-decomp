#include "nitro/types.h"

extern unsigned int *data_ov001_020a04e4;

void func_ov001_0207a880(int value) {
  unsigned int *work;

  work = data_ov001_020a04e4;
  data_ov001_020a04e4[0x3e] = value;
  *work = 0;
  if (value != 0) {
    work[3] = 0;
  }
}

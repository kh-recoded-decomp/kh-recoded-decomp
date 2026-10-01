#include "nitro/types.h"

extern int *data_ov001_020a04cc;

int func_ov001_0207d384(int value) {
  if ((data_ov001_020a04cc != (int *)0x0) && (*data_ov001_020a04cc != 0)) {
    data_ov001_020a04cc[0x3c] = value;
    return 1;
  }
  return 0;
}

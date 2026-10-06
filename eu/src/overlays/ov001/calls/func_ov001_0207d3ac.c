#include "nitro/types.h"

extern int *data_ov001_020a04ec;

int func_ov001_0207d3ac(int value) {
  if ((data_ov001_020a04ec != (int *)0x0) && (*data_ov001_020a04ec != 0)) {
    data_ov001_020a04ec[0x3c] = value;
    return 1;
  }
  return 0;
}

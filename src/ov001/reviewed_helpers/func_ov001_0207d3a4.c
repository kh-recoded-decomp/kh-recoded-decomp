#include "nitro/types.h"

extern int *data_ov001_020a04cc;

int func_ov001_0207d3a4(int delta) {
  if ((data_ov001_020a04cc != (int *)0x0) &&
     (((*data_ov001_020a04cc == 1 || (*data_ov001_020a04cc == 3)) && (delta != 0)))) {
    if (data_ov001_020a04cc[1] != 2) {
      data_ov001_020a04cc[0x47] = data_ov001_020a04cc[0x47] + delta;
    }
    return 1;
  }
  return 0;
}

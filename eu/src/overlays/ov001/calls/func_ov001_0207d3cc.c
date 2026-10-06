#include "nitro/types.h"

extern int *data_ov001_020a04ec;

int func_ov001_0207d3cc(int delta) {
  if ((data_ov001_020a04ec != (int *)0x0) &&
     (((*data_ov001_020a04ec == 1 || (*data_ov001_020a04ec == 3)) && (delta != 0)))) {
    if (data_ov001_020a04ec[1] != 2) {
      data_ov001_020a04ec[0x47] = data_ov001_020a04ec[0x47] + delta;
    }
    return 1;
  }
  return 0;
}

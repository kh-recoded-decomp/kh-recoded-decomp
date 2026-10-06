#include "nitro/types.h"

extern unsigned int *data_ov021_020b56c0;
extern unsigned int Camera_HasPendingModeChange();

unsigned int func_ov021_020af830(void) {
  unsigned int result;

  switch(*data_ov021_020b56c0) {
  case 0:
    result = Camera_HasPendingModeChange();
    return result;
  case 1:
    return 0;
  case 2:
    return 0;
  case 3:
    return 0;
  default:
    return 0;
  }
}

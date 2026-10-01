#include "nitro/types.h"

extern unsigned int *data_ov021_020b56a0;
extern unsigned int func_ov046_020c1750();

unsigned int func_ov021_020af810(void) {
  unsigned int result;

  switch(*data_ov021_020b56a0) {
  case 0:
    result = func_ov046_020c1750();
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

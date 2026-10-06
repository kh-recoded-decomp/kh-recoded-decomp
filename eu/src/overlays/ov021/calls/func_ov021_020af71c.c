#include "nitro/types.h"

extern unsigned int *data_ov021_020b56c0;
extern unsigned int func_ov043_020bd0ac();
extern unsigned int func_ov044_020d0bc4();
extern unsigned int func_ov046_020c170c();

unsigned int func_ov021_020af71c(void) {
  unsigned int result;

  switch(*data_ov021_020b56c0) {
  case 0:
    result = func_ov046_020c170c();
    return result;
  case 1:
  case 2:
    result = func_ov043_020bd0ac();
    return result;
  case 3:
    result = func_ov044_020d0bc4();
    return result;
  default:
    return 0;
  }
}

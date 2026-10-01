#include "nitro/types.h"

extern unsigned int *data_ov021_020b56a0;
extern unsigned int func_ov043_020bd08c();
extern unsigned int func_ov044_020d0ba4();
extern unsigned int func_ov046_020c16ec();

unsigned int func_ov021_020af6fc(void) {
  unsigned int result;

  switch(*data_ov021_020b56a0) {
  case 0:
    result = func_ov046_020c16ec();
    return result;
  case 1:
  case 2:
    result = func_ov043_020bd08c();
    return result;
  case 3:
    result = func_ov044_020d0ba4();
    return result;
  default:
    return 0;
  }
}

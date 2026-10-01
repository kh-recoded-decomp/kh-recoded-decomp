#include "nitro/types.h"

extern unsigned int *data_ov021_020b56a0;
extern unsigned int IsWithinPlaneSet_0203e958();
extern unsigned int func_0203eab0();
extern unsigned int func_ov043_020bd1ec();

int func_ov021_020af738(void *point,int planes) {
  int result;

  switch(*data_ov021_020b56a0) {
  case 0:
    result = IsWithinPlaneSet_0203e958(point,planes);
    return result;
  case 1:
    result = func_0203eab0();
    return result;
  case 2:
    result = func_ov043_020bd1ec();
    return result;
  case 3:
    result = IsWithinPlaneSet_0203e958(point,planes);
    return result;
  default:
    return 0;
  }
}

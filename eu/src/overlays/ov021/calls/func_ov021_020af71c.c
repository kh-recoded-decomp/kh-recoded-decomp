#include "nitro/types.h"

extern unsigned int *data_ov021_020b56c0;
extern unsigned int Ov043Camera_GetViewState();
extern unsigned int Panel_GetViewState();
extern unsigned int Camera_GetViewPlaneNormals();

unsigned int func_ov021_020af71c(void) {
  unsigned int result;

  switch(*data_ov021_020b56c0) {
  case 0:
    result = Camera_GetViewPlaneNormals();
    return result;
  case 1:
  case 2:
    result = Ov043Camera_GetViewState();
    return result;
  case 3:
    result = Panel_GetViewState();
    return result;
  default:
    return 0;
  }
}

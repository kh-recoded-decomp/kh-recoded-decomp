#include "nitro/types.h"

extern unsigned int *gActiveSubModeState;
extern unsigned int Camera_HasPendingModeChange();

unsigned int HasDefaultSubModeCameraChangePending(void) {
  unsigned int result;

  switch(*gActiveSubModeState) {
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

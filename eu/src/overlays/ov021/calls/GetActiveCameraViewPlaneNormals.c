#include "nitro/types.h"

extern unsigned int *gActiveSubModeState;
extern unsigned int Ov043Camera_GetViewState();
extern unsigned int Panel_GetViewState();
extern unsigned int Camera_GetViewPlaneNormals();

unsigned int GetActiveCameraViewPlaneNormals(void) {
  unsigned int result;

  switch(*gActiveSubModeState) {
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

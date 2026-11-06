#include "nitro/types.h"

extern unsigned int *gActiveSubModeState;
extern unsigned int IsWithinPlaneSet_0203ebdc();
extern unsigned int IsPointInViewBounds();
extern unsigned int IsPointInViewDepth();

int IsPointWithinActiveCameraView(void *point,int planes) {
  int result;

  switch(*gActiveSubModeState) {
  case 0:
    result = IsWithinPlaneSet_0203ebdc(point,planes);
    return result;
  case 1:
    result = IsPointInViewBounds();
    return result;
  case 2:
    result = IsPointInViewDepth();
    return result;
  case 3:
    result = IsWithinPlaneSet_0203ebdc(point,planes);
    return result;
  default:
    return 0;
  }
}

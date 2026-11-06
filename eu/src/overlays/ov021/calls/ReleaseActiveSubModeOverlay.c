#include "nitro/types.h"

extern unsigned int *gActiveSubModeState;
extern unsigned char gSubModeOverlayIds;
extern unsigned int NNSi_FndFreeToExpHeap();
extern unsigned int ReleaseOv042CameraNoop();
extern unsigned int UnloadOverlayAfterGeometryTransfer();
extern unsigned int ReleaseOv043CameraNoop();
extern unsigned int ReleaseOv044PanelCameraNoop();
extern unsigned int ReleaseCameraLayerResources();

void ReleaseActiveSubModeOverlay(void) {
  switch(*gActiveSubModeState) {
  case 0:
    ReleaseCameraLayerResources();
    break;
  case 1:
    ReleaseOv042CameraNoop();
    break;
  case 2:
    ReleaseOv043CameraNoop();
    break;
  case 3:
    ReleaseOv044PanelCameraNoop();
  }
  UnloadOverlayAfterGeometryTransfer(0,*(int *)(&gSubModeOverlayIds + *gActiveSubModeState * 4));
  *gActiveSubModeState = -1;
  NNSi_FndFreeToExpHeap
            ((void *)gActiveSubModeState[1],(void *)gActiveSubModeState[3]);
  gActiveSubModeState[1] = 0;
}

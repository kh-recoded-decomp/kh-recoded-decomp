#include "nitro/types.h"

extern unsigned int *data_ov021_020b56c0;
extern unsigned char gSubModeOverlayIds;
extern unsigned int NNSi_FndFreeToExpHeap();
extern unsigned int ReleaseOv042CameraNoop();
extern unsigned int UnloadOverlayAfterGeometryTransfer();
extern unsigned int ReleaseOv043CameraNoop();
extern unsigned int ReleaseOv044PanelCameraNoop();
extern unsigned int ReleaseCameraLayerResources();

void func_ov021_020af3a0(void) {
  switch(*data_ov021_020b56c0) {
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
  UnloadOverlayAfterGeometryTransfer(0,*(int *)(&gSubModeOverlayIds + *data_ov021_020b56c0 * 4));
  *data_ov021_020b56c0 = -1;
  NNSi_FndFreeToExpHeap
            ((void *)data_ov021_020b56c0[1],(void *)data_ov021_020b56c0[3]);
  data_ov021_020b56c0[1] = 0;
}

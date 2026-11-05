#include "nitro/types.h"

extern unsigned int gCameraManager;
extern unsigned int gCameraLayerIdsByMode;
extern unsigned int Obj_FreeDataBuffers();
extern unsigned int UnloadOverlayAfterGeometryTransfer();

void ReleaseCameraLayerResources(void) {
  Obj_FreeDataBuffers((void *)(gCameraManager + 0xf8));
  UnloadOverlayAfterGeometryTransfer(0,((int *)&gCameraLayerIdsByMode)[*(int *)(gCameraManager + 0x80)]);
}

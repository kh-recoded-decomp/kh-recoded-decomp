#include "nitro/types.h"

extern unsigned int gCameraManager;
extern unsigned int gCameraLayerIdsByMode;
extern unsigned int Obj_FreeDataBuffers();
extern unsigned int func_02029fac();

void ReleaseCameraLayerResources(void) {
  Obj_FreeDataBuffers((void *)(gCameraManager + 0xf8));
  func_02029fac(0,((int *)&gCameraLayerIdsByMode)[*(int *)(gCameraManager + 0x80)]);
}

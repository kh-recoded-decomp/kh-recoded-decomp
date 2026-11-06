#include "nitro/types.h"

extern unsigned int gCameraManager;
extern unsigned char gCameraModePresetHeightHead;

int Camera_GetPresetHeight(int index) {
  int value;

  value = *(int *)(&gCameraModePresetHeightHead + index * 0xc);
  if ((*(u32 *)(gCameraManager + 0xf0) & 0x80000) != 0) {
    value = value + 0x2000;
  }
  return value;
}

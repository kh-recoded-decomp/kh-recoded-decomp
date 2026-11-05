#include "nitro/types.h"

extern unsigned int gCameraManager;
extern unsigned char data_ov046_020c33d4;

int Camera_GetPresetHeight(int index) {
  int value;

  value = *(int *)(&data_ov046_020c33d4 + index * 0xc);
  if ((*(u32 *)(gCameraManager + 0xf0) & 0x80000) != 0) {
    value = value + 0x2000;
  }
  return value;
}

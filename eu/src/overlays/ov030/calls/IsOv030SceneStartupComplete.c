#include "nitro/types.h"

extern unsigned int data_ov030_020bd020;

BOOL IsOv030SceneStartupComplete(void) {
  if (data_ov030_020bd020 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov030_020bd020 + 6) & 1) == 0;
}

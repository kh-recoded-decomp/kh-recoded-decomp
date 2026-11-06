#include "nitro/types.h"

extern unsigned int gOv030SceneWork;

BOOL IsOv030SceneStartupComplete(void) {
  if (gOv030SceneWork == 0) {
    return FALSE;
  }
  return (*(u16 *)(gOv030SceneWork + 6) & 1) == 0;
}

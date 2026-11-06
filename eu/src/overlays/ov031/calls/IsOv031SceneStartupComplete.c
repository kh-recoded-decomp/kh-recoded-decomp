#include "nitro/types.h"

extern unsigned int gOv031SceneWorkStorage;

BOOL IsOv031SceneStartupComplete(void) {
  if (gOv031SceneWorkStorage == 0) {
    return FALSE;
  }
  return (*(u16 *)(gOv031SceneWorkStorage + 6) & 1) == 0;
}

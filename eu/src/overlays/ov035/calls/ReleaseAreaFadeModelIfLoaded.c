#include "nitro/types.h"

extern unsigned int gAreaSceneMaterialFadeWork;
extern unsigned int ReleaseResourceAndDetach();

void ReleaseAreaFadeModelIfLoaded(void) {
  int actor;

  actor = gAreaSceneMaterialFadeWork;
  if (*(u8 *)(gAreaSceneMaterialFadeWork + 0x10b) != '\0') {
    ReleaseResourceAndDetach(gAreaSceneMaterialFadeWork);
    *(u8 *)(actor + 0x10b) = 0;
  }
}

#include "nitro/types.h"

extern u32 NextSharedRandom16Scaled();

void NextRandomArrowDirection(void) {
  NextSharedRandom16Scaled(10);
  NextSharedRandom16Scaled(4);
}

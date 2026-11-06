#include "nitro/types.h"

extern u32 gAreaRewardSceneWork;
extern u32 DrawNodeWithExplicitProjection();

void DrawAreaRewardModel(void) {
  DrawNodeWithExplicitProjection
            (gAreaRewardSceneWork,(void *)((int)gAreaRewardSceneWork + 0x104),0x2400,-0x2400,-0x3000
             ,0x3000);
}

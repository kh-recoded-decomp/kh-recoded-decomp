#include "src/overlays/ov001/StageMotionState.h"
#include "src/overlays/ov001/StageManagerFlags.h"


void SetStageManagerFlagBits(u32 mask) {
  if (gStageManager != NULL) {
    gStageManager->flags = mask | gStageManager->flags;
  }
}

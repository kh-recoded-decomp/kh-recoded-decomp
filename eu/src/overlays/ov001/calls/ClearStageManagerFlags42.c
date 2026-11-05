#include "src/overlays/ov001/StageMotionState.h"
#include "src/overlays/ov001/StageManagerFlags.h"


void ClearStageManagerFlags42(void) {
  if (gStageManager != NULL) {
    gStageManager->flags = gStageManager->flags & 0xffffffbd;
  }
}

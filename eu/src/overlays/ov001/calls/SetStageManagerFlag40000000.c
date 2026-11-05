#include "src/overlays/ov001/StageMotionState.h"
#include "src/overlays/ov001/StageManagerFlags.h"


void SetStageManagerFlag40000000(void) {
  if (gStageManager != NULL) {
    gStageManager->flags = gStageManager->flags | 0x40000000;
  }
}

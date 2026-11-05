#include "src/overlays/ov001/StageMotionState.h"
#include "src/overlays/ov001/StageManagerFlags.h"


void func_ov001_0209c440(void) {
  if (gStageManager != NULL) {
    gStageManager->flags = gStageManager->flags & 0xffffffce;
  }
}

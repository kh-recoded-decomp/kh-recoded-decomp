#include "src/overlays/ov001/StageMotionState.h"
#include "src/overlays/ov001/StageManagerFlags.h"


u32 GetMaskedStageManagerFlags(u32 mask) {
  if (gStageManager != NULL) {
    return mask & gStageManager->flags;
  }
  return 0;
}

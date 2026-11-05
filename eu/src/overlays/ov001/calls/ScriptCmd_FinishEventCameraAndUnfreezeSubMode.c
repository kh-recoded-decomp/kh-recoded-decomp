#include "nitro/types.h"

extern u32 FinishEventCameraCut();
extern u32 SetSubModeFrozen();

u32 ScriptCmd_FinishEventCameraAndUnfreezeSubMode(void) {
  FinishEventCameraCut();
  SetSubModeFrozen(0);
  return 1;
}

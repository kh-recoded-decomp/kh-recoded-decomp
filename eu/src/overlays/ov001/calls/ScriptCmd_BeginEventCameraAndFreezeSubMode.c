#include "nitro/types.h"

extern u32 InitFieldCameraFromPreset();
extern u32 SetSubModeFrozen();

u32 ScriptCmd_BeginEventCameraAndFreezeSubMode(void) {
  InitFieldCameraFromPreset();
  SetSubModeFrozen(1);
  return 1;
}

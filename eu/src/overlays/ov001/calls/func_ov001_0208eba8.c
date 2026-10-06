#include "nitro/types.h"

extern u32 InitFieldCameraFromPreset();
extern u32 SetSubModeFrozen();

u32 func_ov001_0208eba8(void) {
  InitFieldCameraFromPreset();
  SetSubModeFrozen(1);
  return 1;
}

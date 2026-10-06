#include "nitro/types.h"

extern u32 FinishEventCameraCut();
extern u32 SetSubModeFrozen();

u32 func_ov001_0208ebb8(void) {
  FinishEventCameraCut();
  SetSubModeFrozen(0);
  return 1;
}

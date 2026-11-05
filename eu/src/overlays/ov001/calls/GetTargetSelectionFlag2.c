#include "nitro/types.h"

extern u32 *data_ov001_020a04a4;

u32 GetTargetSelectionFlag2(void) {
  if (data_ov001_020a04a4 == (u32 *)0x0) {
    return 0;
  }
  return *data_ov001_020a04a4 & 2;
}

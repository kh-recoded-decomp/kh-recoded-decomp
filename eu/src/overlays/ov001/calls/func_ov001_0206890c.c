#include "nitro/types.h"

extern u32 ResetStageGroupRowsAndRestoreDefaultIfActive();

void func_ov001_0206890c(u32 value) {
  ResetStageGroupRowsAndRestoreDefaultIfActive(value & 0xffff);
}

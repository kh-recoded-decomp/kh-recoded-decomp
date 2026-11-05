#include "nitro/types.h"

extern u32 ResetStageGroupRowsAndRestoreDefaultIfActive();

void ResetStageGroupRowsAndRestoreDefault(u32 value) {
  ResetStageGroupRowsAndRestoreDefaultIfActive(value & 0xffff);
}

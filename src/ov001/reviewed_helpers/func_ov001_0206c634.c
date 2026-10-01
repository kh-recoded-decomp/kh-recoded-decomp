#include "nitro/types.h"

extern u32 *data_ov001_020a0484;
extern u32 FindNearestTargetInRange_0206af7c();

void func_ov001_0206c634(int enableFirst,int enableSecond) {
  u32 *work;

  work = data_ov001_020a0484;
  if (data_ov001_020a0484 != (u32 *)0x0) {
    *data_ov001_020a0484 = *data_ov001_020a0484 & 0xffffff3f;
    if (enableFirst != 0) {
      *work = *work | 0x80;
    }
    if (enableSecond != 0) {
      *work = *work | 0x40;
    }
    FindNearestTargetInRange_0206af7c(work + 1,(void *)0x0);
  }
}

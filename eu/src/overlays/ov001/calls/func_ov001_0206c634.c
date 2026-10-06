#include "nitro/types.h"

extern u32 *data_ov001_020a04a4;
extern u32 FindNearestTargetInRange();

void func_ov001_0206c634(int enableFirst,int enableSecond) {
  u32 *work;

  work = data_ov001_020a04a4;
  if (data_ov001_020a04a4 != (u32 *)0x0) {
    *data_ov001_020a04a4 = *data_ov001_020a04a4 & 0xffffff3f;
    if (enableFirst != 0) {
      *work = *work | 0x80;
    }
    if (enableSecond != 0) {
      *work = *work | 0x40;
    }
    FindNearestTargetInRange(work + 1,(void *)0x0);
  }
}

#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 SetRecordEntryEnabled();
extern u32 SetTimerDuration();
extern u32 func_ov036_020c280c();

void func_ov036_020c1d48(int work) {
  int state;

  state = func_ov036_020c280c(gTextWindowResourceTable + 0x64fc);
  if (state != 9) {
    return;
  }
  SetRecordEntryEnabled(work + 0xb4,0);
  SetRecordEntryEnabled(work + 0xf4,0);
  SetTimerDuration(work,9);
}

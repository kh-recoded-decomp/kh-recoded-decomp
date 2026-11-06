#include "nitro/types.h"

extern u32 *gFieldTargetSelectionWork;
extern u32 FindNearestTargetInRange();

void SetEventSlotAndEntryTargetSearchEnabled(int enableFirst,int enableSecond) {
  u32 *work;

  work = gFieldTargetSelectionWork;
  if (gFieldTargetSelectionWork != (u32 *)0x0) {
    *gFieldTargetSelectionWork = *gFieldTargetSelectionWork & 0xffffff3f;
    if (enableFirst != 0) {
      *work = *work | 0x80;
    }
    if (enableSecond != 0) {
      *work = *work | 0x40;
    }
    FindNearestTargetInRange(work + 1,(void *)0x0);
  }
}

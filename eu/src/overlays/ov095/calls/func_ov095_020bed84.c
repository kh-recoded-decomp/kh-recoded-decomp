#include "nitro/types.h"

extern u32 sOv095_VblankFunc_020c28a8;
extern u32 NotifyBothOrOne();
extern u32 ZeroHalfThenFree();
extern u32 func_02050a58();
extern u32 ReleaseRecordManager();
extern u32 ReleaseRecordSlot();
extern u32 SetStateFlagBits();
extern u32 FreeEntryBuffers();
extern u32 ReleaseScreenResources_020bf9c8();
extern u32 ReleaseSlotPool();
extern u32 FreeSlotBuffers_020c0724();
extern u32 FreeGridCells();

void func_ov095_020bed84(int work) {
  int containerIndex;

  containerIndex = 0;
  NotifyBothOrOne(1,&sOv095_VblankFunc_020c28a8,0);
  FreeGridCells(work);
  FreeSlotBuffers_020c0724(work);
  ReleaseSlotPool(work);
  ReleaseScreenResources_020bf9c8(work);
  FreeEntryBuffers(work);
  func_02050a58();
  ReleaseRecordSlot(1);
  ReleaseRecordSlot(5);
  ReleaseRecordSlot(0);
  ReleaseRecordManager();
  do {
    ZeroHalfThenFree(*(u32 *)(work + containerIndex * 4 + 8));
    containerIndex = containerIndex + 1;
  } while (containerIndex < 3);
  SetStateFlagBits(0,5);
}

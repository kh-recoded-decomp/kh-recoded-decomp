#include "nitro/types.h"

extern u32 sOv093_VblankFunc_020c4d54;
extern u32 NotifyBothOrOne();
extern u32 ReleaseRecordManager();
extern u32 ReleaseRecordSlot();
extern u32 SetStateFlagBits();
extern u32 FreeLoadedFiles();
extern u32 FreeResourceBlocks();
extern u32 ReleaseSceneResources();
extern u32 ReleaseSceneObjManagers();
extern u32 ResetTouchActive();
extern u32 func_ov093_020c3c2c();

void func_ov093_020bed58(int work) {
  func_ov093_020c3c2c(*(u32 *)(work + 0xd1c8));
  NotifyBothOrOne(1,&sOv093_VblankFunc_020c4d54,0);
  ResetTouchActive(work);
  ReleaseSceneObjManagers(work);
  ReleaseSceneResources(work);
  FreeResourceBlocks(work);
  FreeLoadedFiles(work);
  ReleaseRecordSlot(9);
  ReleaseRecordSlot(0);
  ReleaseRecordManager();
  SetStateFlagBits(0,5);
}

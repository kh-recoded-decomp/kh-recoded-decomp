#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 UpdateDisplayObjectListQueued();
extern u32 UnlinkActiveIndexedRecord();

void ReleaseTextWindowSpriteRecords(int work) {
  int recordIndex;
  int slot;

  UpdateDisplayObjectListQueued((void *)(gTextWindowResourceTable + 0x18));
  slot = 0;
  do {
    recordIndex = *(int *)(work + 0xb4 + slot * 0x10);
    if (recordIndex != -1) {
      UnlinkActiveIndexedRecord((void *)(gTextWindowResourceTable + 0x18),recordIndex);
      *(u32 *)(work + 0xb4 + slot * 0x10) = 0xffffffff;
    }
    slot = slot + 1;
  } while (slot < 5);
}

#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState gEvent2DPanelManager;
extern u32 MI_CpuFill8();
extern u32 ReleaseSharedRecordSlot();
extern u32 ReleaseResourceSlot();
extern u32 FreeBufferAndClearStatus();
extern u32 FindOrAcquireOwnerSlot();

void ReleaseEvent2DActorSlot(int ownerId) {
  int index;
  int record;

  record = gEvent2DPanelManager.value;
  index = FindOrAcquireOwnerSlot(ownerId);
  record = index * 0x9c + *(int *)(record + 0x1090);
  if (*(int *)(record + 0x74) != 0) {
    ReleaseResourceSlot(*(int *)(record + 0x74));
    ReleaseSharedRecordSlot(*(u32 *)(record + 0x74));
  }
  FreeBufferAndClearStatus(record);
  MI_CpuFill8(record,0,0x9c);
  *(u32 *)(record + 0x8c) = 0xffffffff;
  *(u32 *)(record + 0x98) = 0xffffffff;
  *(u32 *)(record + 0x94) = 0xffffffff;
}

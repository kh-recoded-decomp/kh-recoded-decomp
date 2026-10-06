#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov036_020c3940;
extern u32 MI_CpuFill8();
extern u32 ReleaseSharedRecordSlot();
extern u32 ReleaseResourceSlot();
extern u32 func_ov001_0206a918();
extern u32 FindOrAcquireOwnerSlot();

void func_ov036_020bd090(int ownerId) {
  int index;
  int record;

  record = data_ov036_020c3940.value;
  index = FindOrAcquireOwnerSlot(ownerId);
  record = index * 0x9c + *(int *)(record + 0x1090);
  if (*(int *)(record + 0x74) != 0) {
    ReleaseResourceSlot(*(int *)(record + 0x74));
    ReleaseSharedRecordSlot(*(u32 *)(record + 0x74));
  }
  func_ov001_0206a918(record);
  MI_CpuFill8(record,0,0x9c);
  *(u32 *)(record + 0x8c) = 0xffffffff;
  *(u32 *)(record + 0x98) = 0xffffffff;
  *(u32 *)(record + 0x94) = 0xffffffff;
}

#include "nitro/types.h"

extern u32 data_ov040_020be284;
extern u32 NNSi_FndAllocFromDefaultHeap();
extern u32 GetResourceArchiveId();
extern u32 AcquireRecordHandle();
extern u32 AcquirePaletteEntry();

void func_ov040_020bdf9c(int actor,u32 owner) {
  u32 *handles;
  int archive;
  u32 handle;
  u32 fileBase;

  handles = (u32 *)NNSi_FndAllocFromDefaultHeap(0x14);
  data_ov040_020be284 = handles;
  archive = GetResourceArchiveId(4);
  fileBase = (archive + 0x8000U & 0xfffffc) * 0x80;
  handle = AcquireRecordHandle(actor + 0x1070,owner,0,fileBase | 0x80000000);
  *handles = handle;
  handle = AcquireRecordHandle(actor + 0x1070,owner,0xe,fileBase | 0x8000000e);
  handles[1] = handle;
  handle = AcquirePaletteEntry(actor + 0x1070,owner,0,0);
  handles[2] = handle;
  handles[3] = 0;
}

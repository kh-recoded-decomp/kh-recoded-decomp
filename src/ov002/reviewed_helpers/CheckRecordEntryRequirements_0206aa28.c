#include "nitro/types.h"

extern u32 AcquireRecordSlot_02051d3c();
extern u32 GetRecordTableCEntry_0205225c();
extern u32 ReleaseRecordSlot_02051dfc();
extern u32 func_ov002_0206991c();

BOOL CheckRecordEntryRequirements_0206aa28(int context)

{
  short entryId;
  short *entries;
  int status;
  int index;
  
  AcquireRecordSlot_02051d3c(10,1);
  entries = (short *)(GetRecordTableCEntry_0205225c(context) + 6);
  index = 0;
  do {
    entryId = entries[index];
    if (((-1 < entryId) && (entryId < 0x5a1)) && (status = func_ov002_0206991c(entryId), status <= 0)) break;
    index = index + 1;
  } while (index < 0x14);
  ReleaseRecordSlot_02051dfc(10);
  return index >= 0x14;
}

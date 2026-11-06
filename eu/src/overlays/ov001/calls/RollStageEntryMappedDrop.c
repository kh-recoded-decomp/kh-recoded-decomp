#include "nitro/types.h"

extern unsigned int *gStageEventContext;
extern unsigned int GetCurrentFieldStageCode();
extern unsigned int RollEnemyDrop();
extern unsigned int LookupMappedByteValue();
extern unsigned int GetGroupIndexedValue();

void RollStageEntryMappedDrop(int index,unsigned int secondValue,unsigned int firstValue) {
  int resolvedKind;
  int records;
  u32 kind;

  records = *(int *)(*gStageEventContext + 4);
  kind = (u32)*(u8 *)(records + index * 0xc);
  resolvedKind = GetCurrentFieldStageCode();
  if (resolvedKind == 900) {
    kind = GetGroupIndexedValue(*(u8 *)(records + index * 0xc));
  }
  resolvedKind = LookupMappedByteValue(kind);
  if (resolvedKind != 0x28) {
    RollEnemyDrop(firstValue,resolvedKind,secondValue,1);
  }
}

#include "nitro/types.h"

extern unsigned int *data_ov001_020a0490;
extern unsigned int func_ov001_020644b0();
extern unsigned int RollEnemyDrop();
extern unsigned int LookupMappedByteValue();
extern unsigned int GetGroupIndexedValue();

void func_ov001_02068a74(int index,unsigned int secondValue,unsigned int firstValue) {
  int resolvedKind;
  int records;
  u32 kind;

  records = *(int *)(*data_ov001_020a0490 + 4);
  kind = (u32)*(u8 *)(records + index * 0xc);
  resolvedKind = func_ov001_020644b0();
  if (resolvedKind == 900) {
    kind = GetGroupIndexedValue(*(u8 *)(records + index * 0xc));
  }
  resolvedKind = LookupMappedByteValue(kind);
  if (resolvedKind != 0x28) {
    RollEnemyDrop(firstValue,resolvedKind,secondValue,1);
  }
}

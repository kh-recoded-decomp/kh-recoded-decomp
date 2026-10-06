#include "nitro/types.h"

extern unsigned int MIi_CpuCopy32();
extern unsigned int EntryList_FindByKey();

unsigned int func_ov059_020cf3b4(int actor) {
  int entryIndex;
  u32 remaining;

  entryIndex = EntryList_FindByKey();
  if (entryIndex != -1) {
    remaining = (*(u8 *)(actor + 0x120) - 1) - entryIndex & 0xff;
    if (remaining != 0) {
      MIi_CpuCopy32(actor + 0x60 + (entryIndex + 1) * 8,actor + 0x60 + entryIndex * 8,remaining << 3);
    }
    *(u8 *)(actor + 0x120) = *(u8 *)(actor + 0x120) + -1;
    return 1;
  }
  return 0;
}

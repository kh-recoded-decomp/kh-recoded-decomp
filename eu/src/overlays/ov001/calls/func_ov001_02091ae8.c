#include "nitro/types.h"

extern unsigned int GetStageEntrySlot();
extern unsigned int ReleaseSlotResource();

void func_ov001_02091ae8(int owner,u32 firstId,u32 secondId) {
  u16 *entry;
  u8 *slot;
  int index;

  index = 0;
  do {
    slot = (u8 *)(owner + 0x3b4 + index * 2);
    if ((((slot[1] != '\0') && (entry = (u16 *)GetStageEntrySlot(), entry != (u16 *)0x0)
         ) && (*(int *)(entry + 2) != 0)) &&
       (((firstId == 0xffff && (secondId == 0xffff)) ||
        ((*entry == firstId && (entry[1] == secondId)))))) {
      ReleaseSlotResource(slot[1]);
      slot[1] = 0;
      *slot = 0;
      if (firstId != 0xffff) {
        return;
      }
      if (secondId != 0xffff) {
        return;
      }
    }
    index = index + 1;
    if (index >= 8) {
      return;
    }
  } while( TRUE );
}

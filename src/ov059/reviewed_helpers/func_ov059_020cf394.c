#include "nitro/types.h"

extern unsigned int func_01ff8710();
extern unsigned int func_ov059_020cf3e8();

unsigned int func_ov059_020cf394(int actor) {
  int entryIndex;
  u32 remaining;

  entryIndex = func_ov059_020cf3e8();
  if (entryIndex != -1) {
    remaining = (*(u8 *)(actor + 0x120) - 1) - entryIndex & 0xff;
    if (remaining != 0) {
      func_01ff8710(actor + 0x60 + (entryIndex + 1) * 8,actor + 0x60 + entryIndex * 8,remaining << 3);
    }
    *(u8 *)(actor + 0x120) = *(u8 *)(actor + 0x120) + -1;
    return 1;
  }
  return 0;
}

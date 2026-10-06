#include "nitro/types.h"

u32 func_ov059_020cf46c(int actor,u32 firstId,u32 secondId) {
  int entry;
  u32 index;

  index = 0;
  if (index < (u32)*(u8 *)(actor + 0x120)) {
    do {
      entry = actor + index * 8;
      if (((*(int *)(entry + 100) == 2) && (firstId == *(u16 *)(entry + 0x60))) &&
         (secondId == *(u16 *)(entry + 0x62))) {
        return index;
      }
      index = index + 1 & 0xff;
    } while (index < *(u8 *)(actor + 0x120));
  }
  return 0xffffffff;
}

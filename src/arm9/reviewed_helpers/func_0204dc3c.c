#include "nitro/types.h"

extern unsigned int data_0206084c;

BOOL func_0204dc3c(u32 handle) {
  int soundSlot;

  soundSlot = data_0206084c + 0xb4518 + (handle >> 0x18) * 0x20;
  if ((*(unsigned short *)(soundSlot + 0x14) != 0) && (*(u32 *)(soundSlot + 0x18) == (handle & 0xffffff))) {
    return *(int *)(soundSlot + 0x1c) != 0;
  }
  return FALSE;
}

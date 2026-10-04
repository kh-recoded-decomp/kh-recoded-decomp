#include "nitro/types.h"

extern void LoadDefaultProjectionValues_0202a7b4(void *projection);

void InitModelCamera_020c1b24(u8 *viewer) {
  LoadDefaultProjectionValues_0202a7b4(viewer + 0x5c0);
  *(u32 *)(viewer + 0x5e8) = 0x3000;
  *(u32 *)(viewer + 0x5e4) = 0x1000;
  *(u32 *)(viewer + 0x5d8) = 0x1000;
}

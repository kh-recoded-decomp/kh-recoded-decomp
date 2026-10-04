#include "nitro/types.h"

extern void func_01ff8830(void *dst, int value, int size);
extern void func_02006d3c(int value);
extern void func_ov099_020c1a98(u8 *viewer);
extern void InitModelCamera_020c1b24(u8 *viewer);
extern void func_ov099_020c2058(u8 *viewer, int selection);

void ResetModelViewer_020c214c(u8 *viewer) {
  func_01ff8830(viewer, 0, 0x5f8);
  *(int *)(viewer + 0x5bc) = -1;
  func_02006d3c(-0x44);
  func_ov099_020c1a98(viewer);
  InitModelCamera_020c1b24(viewer);
  func_ov099_020c2058(viewer, 0);
}

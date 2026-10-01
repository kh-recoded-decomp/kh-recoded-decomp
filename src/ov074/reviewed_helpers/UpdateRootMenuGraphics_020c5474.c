#include "nitro/types.h"

extern u32 camera_commit_projection_0202a814();
extern u32 func_01ffb12c();
extern u32 func_0202ef24();
extern u32 func_ov021_020a9aa4();
extern u32 func_ov021_020a9af0();
extern u32 func_ov074_020c5108();
extern u32 func_ov074_020c5250();

void UpdateRootMenuGraphics_020c5474(int context)

{
  if (*(u8 *)(context + 2) != '\0') {
    func_ov074_020c5108(context);
    func_ov074_020c5250(context);
    *(u8 *)(context + 2) = *(u8 *)(context + 2) + -1;
  }
  if (*(int *)(context + 8) == 0) {
    return;
  }
  camera_commit_projection_0202a814(context + 0x400);
  func_0202ef24(context + 0x1c,0x1000);
  func_01ffb12c(context + 0x1c);
  if (*(int *)(context + 0xc) == 0) {
    return;
  }
  func_ov021_020a9aa4(context + 0x120,0x1000);
  func_ov021_020a9af0(context + 0x120);
  return;
}

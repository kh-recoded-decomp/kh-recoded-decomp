#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern u32 BeginScreenFadeOut();
extern u32 IsScreenModeIdle();
extern u32 func_ov001_0206685c();

u32 func_ov028_020bacd0(void) {
  int work;
  u32 busy;
  int idle;

  work = data_ov028_020bb3a0;
  if (((*(u16 *)(data_ov028_020bb3a0 + 6) & 0x10) == 0) &&
     (busy = func_ov001_0206685c(), busy != 0)) {
    return 0xffffffff;
  }
  idle = IsScreenModeIdle();
  if (idle != 0) {
    BeginScreenFadeOut((int)*(char *)(work + 8));
    return 0x10;
  }
  return 0xffffffff;
}

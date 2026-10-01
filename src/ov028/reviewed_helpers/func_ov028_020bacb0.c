#include "nitro/types.h"

extern u32 data_ov028_020bb380;
extern u32 BeginScreenFadeOut_0206a7c0();
extern u32 IsScreenModeIdle_0206a814();
extern u32 func_ov001_0206685c();

u32 func_ov028_020bacb0(void) {
  int work;
  u32 busy;
  int idle;

  work = data_ov028_020bb380;
  if (((*(u16 *)(data_ov028_020bb380 + 6) & 0x10) == 0) &&
     (busy = func_ov001_0206685c(), busy != 0)) {
    return 0xffffffff;
  }
  idle = IsScreenModeIdle_0206a814();
  if (idle != 0) {
    BeginScreenFadeOut_0206a7c0((int)*(char *)(work + 8));
    return 0x10;
  }
  return 0xffffffff;
}

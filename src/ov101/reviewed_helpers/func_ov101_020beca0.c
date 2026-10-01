#include "nitro/types.h"

extern u32 data_ov101_020c4d20;
extern u32 NotifyBothOrOne_02001154();
extern u32 func_ov039_020bc688();
extern u32 func_ov101_020bf290();
extern u32 func_ov101_020bf3d0();
extern u32 func_ov101_020bf5c4();
extern u32 func_ov101_020bfa1c();
extern u32 func_ov101_020c06c0();

void func_ov101_020beca0(u32 work) {
  NotifyBothOrOne_02001154(1,0x20c1378,0);
  func_ov101_020c06c0(work);
  func_ov101_020bfa1c(work);
  func_ov101_020bf5c4(work);
  func_ov101_020bf3d0(work);
  func_ov101_020bf290(work);
  func_ov039_020bc688(0,5);
  data_ov101_020c4d20 = 0;
}

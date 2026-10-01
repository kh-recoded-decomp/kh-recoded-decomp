#include "nitro/types.h"

extern u32 data_ov036_020c3844;
extern u32 func_0204f5d8();
extern u32 func_ov036_020beb1c();
extern u32 func_ov036_020beb9c();
extern u32 func_ov036_020bf4d4();

void func_ov036_020be8f4(void) {
  func_ov036_020bf4d4();
  func_ov036_020beb9c();
  func_ov036_020beb1c();
  func_0204f5d8(data_ov036_020c3844 + 0x6830);
  data_ov036_020c3844 = 0;
}

#include "nitro/types.h"

extern u32 *data_ov001_020a0528;

void func_ov001_0209c5c4(u32 mask) {
  if (data_ov001_020a0528 != (u32 *)0x0) {
    *data_ov001_020a0528 = mask | *data_ov001_020a0528;
  }
}

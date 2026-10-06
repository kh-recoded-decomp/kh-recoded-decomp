#include "nitro/types.h"

extern u32 *data_ov001_020a0528;

void func_ov001_0209c554(void) {
  if (data_ov001_020a0528 != (u32 *)0x0) {
    *data_ov001_020a0528 = *data_ov001_020a0528 | 0x40000000;
  }
}

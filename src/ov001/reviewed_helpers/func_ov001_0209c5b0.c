#include "nitro/types.h"

extern u32 *data_ov001_020a0508;

void func_ov001_0209c5b0(u32 mask) {
  if (data_ov001_020a0508 != (u32 *)0x0) {
    *data_ov001_020a0508 = ~mask & *data_ov001_020a0508;
  }
}

#include "nitro/types.h"

extern u32 *data_ov001_020a0484;

u32 func_ov001_0206c2c8(void) {
  if (data_ov001_020a0484 == (u32 *)0x0) {
    return 0;
  }
  return *data_ov001_020a0484 & 2;
}

#include "nitro/types.h"

extern u32 *data_ov001_020a0508;

u32 func_ov001_0209c584(u32 mask) {
  if (data_ov001_020a0508 != (u32 *)0x0) {
    return mask & *data_ov001_020a0508;
  }
  return 0;
}

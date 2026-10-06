#include "nitro/types.h"

extern u32 *data_ov001_020a04a4;

u32 func_ov001_0206c504(void) {
  if (data_ov001_020a04a4 == (u32 *)0x0) {
    return 0x7fffffff;
  }
  if ((*data_ov001_020a04a4 & 4) != 0) {
    return 0x7fffffff;
  }
  return data_ov001_020a04a4[0xd];
}

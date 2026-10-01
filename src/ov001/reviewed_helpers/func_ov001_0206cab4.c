#include "nitro/types.h"

extern u32 *data_ov001_020a0498;

void func_ov001_0206cab4(int enabled) {
  if (data_ov001_020a0498 != (u32 *)0x0) {
    if (enabled != 0) {
      *data_ov001_020a0498 = *data_ov001_020a0498 | 1;
      return;
    }
    *data_ov001_020a0498 = *data_ov001_020a0498 & 0xfffffffe;
  }
}

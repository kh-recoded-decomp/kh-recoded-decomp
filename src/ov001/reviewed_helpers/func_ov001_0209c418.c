#include "nitro/types.h"

extern u32 *data_ov001_020a0508;

void func_ov001_0209c418(void) {
  if (data_ov001_020a0508 != (u32 *)0x0) {
    *data_ov001_020a0508 = *data_ov001_020a0508 & 0xffffffce;
  }
}

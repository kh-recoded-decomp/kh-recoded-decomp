#include "nitro/types.h"

extern u32 data_ov042_020be5c0;

void func_ov042_020be49c(u32 value) {
  *(u32 *)(data_ov042_020be5c0 + 0x144) = value;
}

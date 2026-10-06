#include "nitro/types.h"

extern u32 data_ov042_020be5e0;

void func_ov042_020be4bc(u32 value) {
  *(u32 *)(data_ov042_020be5e0 + 0x144) = value;
}

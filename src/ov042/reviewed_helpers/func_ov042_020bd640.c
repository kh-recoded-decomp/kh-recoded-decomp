#include "nitro/types.h"

extern u32 data_ov042_020be5c0;

void func_ov042_020bd640(u32 value) {
  *(u32 *)(data_ov042_020be5c0 + 0x13c) = 0x7fffffff;
  *(u32 *)(data_ov042_020be5c0 + 200) = value;
}

#include "nitro/types.h"

extern u32 data_ov042_020be5e0;

void func_ov042_020bd7c8(u32 firstValue,int secondValue) {
  if ((*(int *)(data_ov042_020be5e0 + 200) != 0x7fffffff) && (secondValue == 0x7fffffff)) {
    *(u32 *)(data_ov042_020be5e0 + 0xd4) = 0;
    *(u32 *)(data_ov042_020be5e0 + 0xd0) = *(u32 *)(data_ov042_020be5e0 + 0x70);
  }
  *(u32 *)(data_ov042_020be5e0 + 0xc4) = firstValue;
  *(int *)(data_ov042_020be5e0 + 200) = secondValue;
  if (secondValue != 0x7fffffff) {
    *(u32 *)(data_ov042_020be5e0 + 0x140) = *(u32 *)(data_ov042_020be5e0 + 0x140) | 1;
    *(u32 *)(data_ov042_020be5e0 + 0xcc) = *(u32 *)(data_ov042_020be5e0 + 0x70);
  }
  *(u32 *)(data_ov042_020be5e0 + 0x13c) = 0x7fffffff;
}

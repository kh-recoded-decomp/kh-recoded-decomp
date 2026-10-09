#include "nitro/types.h"

extern u32 data_ov042_020be5e0;

void SetCameraParameterC4(u32 value) {
  *(u32 *)(data_ov042_020be5e0 + 0x13c) = 0x7fffffff;
  *(u32 *)(data_ov042_020be5e0 + 0xc4) = value;
}

#include "nitro/types.h"

extern u32 data_ov042_020be5e0;

void SetCameraFollowMaxY(u32 value) {
  *(u32 *)(data_ov042_020be5e0 + 0x13c) = 0x7fffffff;
  *(u32 *)(data_ov042_020be5e0 + 0xc0) = value;
}

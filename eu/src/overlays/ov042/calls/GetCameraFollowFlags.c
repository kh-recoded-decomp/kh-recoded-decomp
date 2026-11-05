#include "nitro/types.h"

extern u32 data_ov042_020be5e0;

u32 GetCameraFollowFlags(void) {
  return *(u32 *)(data_ov042_020be5e0 + 0x140);
}

#include "nitro/types.h"

extern u32 data_ov042_020be5c0;

u32 func_ov042_020bd0d4(void) {
  if (data_ov042_020be5c0 != 0) {
    return *(u32 *)(data_ov042_020be5c0 + 0x38) & 0x800;
  }
  return 0;
}

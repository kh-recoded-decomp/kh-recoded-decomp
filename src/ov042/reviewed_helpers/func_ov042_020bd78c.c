#include "nitro/types.h"

extern u32 data_ov042_020be5c0;

u32 func_ov042_020bd78c(void) {
  if (*(int *)(data_ov042_020be5c0 + 0x148) != 0) {
    return 1;
  }
  return 0;
}

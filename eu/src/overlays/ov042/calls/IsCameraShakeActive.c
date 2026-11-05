#include "nitro/types.h"

extern u32 data_ov042_020be5e0;

u32 IsCameraShakeActive(void) {
  if (*(int *)(data_ov042_020be5e0 + 0x148) != 0) {
    return 1;
  }
  return 0;
}

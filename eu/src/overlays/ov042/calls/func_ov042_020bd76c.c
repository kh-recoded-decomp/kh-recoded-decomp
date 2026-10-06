#include "nitro/types.h"

extern u32 data_ov042_020be5e0;
extern u32 InitDriftParticle();
extern u32 func_ov030_020bb374();

void func_ov042_020bd76c(u32 first,u32 second) {
  u32 context;

  *(u32 *)(data_ov042_020be5e0 + 0x38) = *(u32 *)(data_ov042_020be5e0 + 0x38) & 0xffff7fff;
  *(u32 *)(data_ov042_020be5e0 + 0x38) = *(u32 *)(data_ov042_020be5e0 + 0x38) | 0x10000;
  context = func_ov030_020bb374();
  InitDriftParticle(data_ov042_020be5e0 + 0x148,context,first,second);
}

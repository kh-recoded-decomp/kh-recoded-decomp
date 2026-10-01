#include "nitro/types.h"

extern u32 data_ov042_020be5c0;
extern u32 func_ov021_020afb34();
extern u32 func_ov030_020bb354();

void func_ov042_020bd74c(u32 first,u32 second) {
  u32 context;

  *(u32 *)(data_ov042_020be5c0 + 0x38) = *(u32 *)(data_ov042_020be5c0 + 0x38) & 0xffff7fff;
  *(u32 *)(data_ov042_020be5c0 + 0x38) = *(u32 *)(data_ov042_020be5c0 + 0x38) | 0x10000;
  context = func_ov030_020bb354();
  func_ov021_020afb34(data_ov042_020be5c0 + 0x148,context,first,second);
}

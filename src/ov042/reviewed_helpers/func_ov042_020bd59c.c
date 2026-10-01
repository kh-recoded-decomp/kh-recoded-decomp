#include "nitro/types.h"

extern u32 data_ov042_020be5c0;
extern u32 FixedPointMultiply12();
extern u32 func_ov042_020bd858();

void func_ov042_020bd59c(int extent) {
  int work;
  u32 scaledExtent;

  work = data_ov042_020be5c0;
  if (extent < 0x1000) {
    extent = 0x1000;
  }
  *(int *)(data_ov042_020be5c0 + 0x5c) = extent;
  *(int *)(work + 0x60) = -extent;
  *(int *)(work + 0x54) = -extent;
  *(int *)(work + 0x58) = extent;
  scaledExtent = FixedPointMultiply12(extent,*(u32 *)(work + 8));
  *(u32 *)(work + 0x58) = scaledExtent;
  scaledExtent = FixedPointMultiply12(*(u32 *)(work + 0x54),*(u32 *)(work + 8));
  *(u32 *)(work + 0x54) = scaledExtent;
  func_ov042_020bd858();
}

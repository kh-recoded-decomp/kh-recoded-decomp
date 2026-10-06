#include "nitro/types.h"

extern u32 data_ov042_020be5e0;
extern u32 GetEntryFieldForMode();

void func_ov042_020bd830(int *outFirst,int *outSecond) {
  int *entry;
  int offset;

  *outFirst = *(int *)(data_ov042_020be5e0 + 0xc4) + *(int *)(data_ov042_020be5e0 + 0x54);
  *outSecond = *(int *)(data_ov042_020be5e0 + 200) + *(int *)(data_ov042_020be5e0 + 0x58);
  entry = (int *)GetEntryFieldForMode(0);
  offset = *(int *)(*(int *)(*entry + 0x130) + 0x28);
  *outFirst = *outFirst + offset;
  *outSecond = *outSecond - offset;
}

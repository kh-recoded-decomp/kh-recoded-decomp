#include "nitro/types.h"

extern u32 func_ov032_020bbc0c();
extern u32 func_ov032_020bbc60();
extern u32 func_ov032_020bbc78();

void AdvanceGroupSettleCounter_020bca54(int object)

{
  u16 linkedId;
  int member;
  int group;
  
  member = func_ov032_020bbc78(object);
  group = func_ov032_020bbc60(object);
  *(short *)(group + 0x1a) = *(short *)(group + 0x1a) + 1;
  if (0x3c <= *(short *)(group + 0x1a)) {
    *(u32 *)(group + 8) = *(u32 *)(group + 8) & 0xfffffffe | 1;
    linkedId = func_ov032_020bbc0c(*(u32 *)(object + 4),(int)*(char *)(member + 2));
    *(u16 *)(group + 0x12) = linkedId;
  }
  return;
}

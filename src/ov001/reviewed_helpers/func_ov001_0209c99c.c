#include "nitro/types.h"

extern unsigned int data_ov001_020a0508;

u32 func_ov001_0209c99c(int startHandle) {
  u32 index;
  int event;

  index = (startHandle - 1U & 0xffff) + 1 & 0xffff;
  if (index < *(u16 *)(data_ov001_020a0508 + 0x18dee)) {
    do {
      event = *(int *)(data_ov001_020a0508 + 0x210) + index * 0x1c8;
      if (*(unsigned short *)(event + 0x10) != 0) {
        return index + 1 & 0xffff;
      }
      if (*(unsigned short *)(event + 0xe) == 99) {
        return index + 1 & 0xffff;
      }
      index = index + 1 & 0xffff;
    } while (index < *(u16 *)(data_ov001_020a0508 + 0x18dee));
  }
  return 0;
}

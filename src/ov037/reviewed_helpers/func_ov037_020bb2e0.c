#include "nitro/types.h"

extern unsigned int data_ov037_020bb764;

void func_ov037_020bb2e0(unsigned int first,unsigned int second) {
  u16 index;
  int records;

  index = *(u16 *)(data_ov037_020bb764 + 2);
  records = data_ov037_020bb764 + 0x1d4;
  *(unsigned int *)(records + (u32)index * 8) = first;
  *(unsigned int *)(records + (u32)index * 8 + 4) = second;
  *(u16 *)(data_ov037_020bb764 + 2) = *(u16 *)(data_ov037_020bb764 + 2) + 1;
}

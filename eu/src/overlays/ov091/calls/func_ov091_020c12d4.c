#include "nitro/types.h"

extern unsigned char data_ov091_020c2ca8;
extern unsigned int IsGlobalPackedBitSet();
extern unsigned int SetEntryFlag();
extern unsigned int SetGlobalPackedBit();

void func_ov091_020c12d4(int work) {
  int flag;
  int completed;
  int index;

  completed = 0;
  index = 0;
  do {
    flag = IsGlobalPackedBitSet(*(int *)(&data_ov091_020c2ca8 + index * 4));
    if (flag != 0) {
      completed = completed + 1;
      SetGlobalPackedBit(index + 0x11b2);
    }
    flag = IsGlobalPackedBitSet(index + 0x1262);
    if ((flag == 0) && (flag = IsGlobalPackedBitSet(index + 0x11b2), flag != 0)) {
      SetEntryFlag(2,2);
    }
    index = index + 1;
  } while (index < 8);
  *(int *)(work + 0xc9fc) = (int)(completed * 100 + ((u32)(completed * 100 >> 2) >> 0x1d)) >> 3;
}

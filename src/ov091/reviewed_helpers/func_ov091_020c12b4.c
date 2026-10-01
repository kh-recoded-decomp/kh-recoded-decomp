#include "nitro/types.h"

extern unsigned char data_ov091_020c2c88;
extern unsigned int IsGlobalPackedBitSet_02027304();
extern unsigned int SetEntryFlag_020c1718();
extern unsigned int SetGlobalPackedBit_02027320();

void func_ov091_020c12b4(int work) {
  int flag;
  int completed;
  int index;

  completed = 0;
  index = 0;
  do {
    flag = IsGlobalPackedBitSet_02027304(*(int *)(&data_ov091_020c2c88 + index * 4));
    if (flag != 0) {
      completed = completed + 1;
      SetGlobalPackedBit_02027320(index + 0x11b2);
    }
    flag = IsGlobalPackedBitSet_02027304(index + 0x1262);
    if ((flag == 0) && (flag = IsGlobalPackedBitSet_02027304(index + 0x11b2), flag != 0)) {
      SetEntryFlag_020c1718(2,2);
    }
    index = index + 1;
  } while (index < 8);
  *(int *)(work + 0xc9fc) = (int)(completed * 100 + ((u32)(completed * 100 >> 2) >> 0x1d)) >> 3;
}

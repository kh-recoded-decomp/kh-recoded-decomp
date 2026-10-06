#include "nitro/types.h"

extern unsigned char data_ov091_020c2d68;
extern unsigned int IsGlobalPackedBitSet();
extern unsigned int ReadGlobalPackedBits();
extern unsigned int SetEntryFlag();
extern unsigned int SetGlobalPackedBit();

void func_ov091_020c1370(int work) {
  u32 progress;
  int flag;
  int completed;
  int index;

  completed = 0;
  index = 0;
  do {
    progress = ReadGlobalPackedBits(*(u32 *)(&data_ov091_020c2d68 + index * 4),0x11);
    if (progress != 0) {
      completed = completed + 1;
      SetGlobalPackedBit(index + 0x1172);
    }
    flag = IsGlobalPackedBitSet(index + 0x1222);
    if ((flag == 0) && (flag = IsGlobalPackedBitSet(index + 0x1172), flag != 0)) {
      SetEntryFlag(2,3);
    }
    index = index + 1;
  } while (index < 0x28);
  *(int *)(work + 0xca00) = (completed * 100) / 0x28;
}

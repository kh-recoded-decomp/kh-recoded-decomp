#include "nitro/types.h"

extern unsigned char data_ov091_020c2d48;
extern unsigned int IsGlobalPackedBitSet_02027304();
extern unsigned int ReadGlobalPackedBits_02027348();
extern unsigned int SetEntryFlag_020c1718();
extern unsigned int SetGlobalPackedBit_02027320();

void func_ov091_020c1350(int work) {
  u32 progress;
  int flag;
  int completed;
  int index;

  completed = 0;
  index = 0;
  do {
    progress = ReadGlobalPackedBits_02027348(*(u32 *)(&data_ov091_020c2d48 + index * 4),0x11);
    if (progress != 0) {
      completed = completed + 1;
      SetGlobalPackedBit_02027320(index + 0x1172);
    }
    flag = IsGlobalPackedBitSet_02027304(index + 0x1222);
    if ((flag == 0) && (flag = IsGlobalPackedBitSet_02027304(index + 0x1172), flag != 0)) {
      SetEntryFlag_020c1718(2,3);
    }
    index = index + 1;
  } while (index < 0x28);
  *(int *)(work + 0xca00) = (completed * 100) / 0x28;
}

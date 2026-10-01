#include "nitro/types.h"

extern unsigned char data_0205356c;
extern unsigned int FixedPointMultiply12();
extern unsigned int func_ov032_020bbc30();

void func_ov032_020bbc80(void *work,int index,int angle,int *position) {
  u32 right;
  int value;
  int tableIndex;

  right = func_ov032_020bbc30(work,index);
  tableIndex = (int)(angle * 0x10000 + ((u32)(angle * 0x10000 >> 3) >> 0x1c)) >> 8;
  value = FixedPointMultiply12((int)*(short *)(&data_0205356c + tableIndex * 2),right);
  *position = value;
  position[1] = -0x8f;
  value = FixedPointMultiply12
                    ((int)*(short *)(&data_0205356c + (0x400U - tableIndex & 0xfff) * 2),right);
  position[2] = value;
}

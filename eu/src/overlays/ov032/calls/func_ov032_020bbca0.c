#include "nitro/types.h"

extern unsigned char gSinFx12Table;
extern unsigned int FX_Mul();
extern unsigned int GetRowMoveSpeed();

void func_ov032_020bbca0(void *work,int index,int angle,int *position) {
  u32 right;
  int value;
  int tableIndex;

  right = GetRowMoveSpeed(work,index);
  tableIndex = (int)(angle * 0x10000 + ((u32)(angle * 0x10000 >> 3) >> 0x1c)) >> 8;
  value = FX_Mul((int)*(short *)(&gSinFx12Table + tableIndex * 2),right);
  *position = value;
  position[1] = -0x8f;
  value = FX_Mul
                    ((int)*(short *)(&gSinFx12Table + (0x400U - tableIndex & 0xfff) * 2),right);
  position[2] = value;
}

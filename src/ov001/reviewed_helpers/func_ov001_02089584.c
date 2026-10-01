#include "nitro/types.h"

extern unsigned char data_0205356c;
extern unsigned int MTX_Concat33_01ff9270();
extern unsigned int MTX_RotX33_01ff9220();
extern unsigned int func_01ff90ec();
extern unsigned int func_01ff923c();
extern unsigned int func_01ff9258();

void func_ov001_02089584(void *matrix,int xAngle,int yAngle,int zAngle) {
  u8 rotation [36];

  func_01ff90ec();
  func_01ff90ec(rotation);
  MTX_RotX33_01ff9220
            (rotation,(int)*(short *)(&data_0205356c + (xAngle >> 4) * 2),
             (int)*(short *)(&data_0205356c + (0x400U - (xAngle >> 4) & 0xfff) * 2));
  MTX_Concat33_01ff9270(matrix,rotation,matrix);
  func_01ff90ec(rotation);
  func_01ff923c(rotation,(int)*(short *)(&data_0205356c + (yAngle >> 4) * 2),
                      (int)*(short *)(&data_0205356c + (0x400U - (yAngle >> 4) & 0xfff) * 2))
  ;
  MTX_Concat33_01ff9270(matrix,rotation,matrix);
  func_01ff90ec(rotation);
  func_01ff9258(rotation,(int)*(short *)(&data_0205356c + (zAngle >> 4) * 2),
                      (int)*(short *)(&data_0205356c + (0x400U - (zAngle >> 4) & 0xfff) * 2))
  ;
  MTX_Concat33_01ff9270(matrix,rotation,matrix);
}

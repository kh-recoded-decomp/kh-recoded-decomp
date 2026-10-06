#include "nitro/types.h"

extern unsigned char data_02053580;
extern unsigned int MTX_Concat33();
extern unsigned int MTX_RotX33_();
extern unsigned int MTX_Identity33_();
extern unsigned int MTX_RotY33_();
extern unsigned int MTX_RotZ33_();

void func_ov001_020895ac(void *matrix,int xAngle,int yAngle,int zAngle) {
  u8 rotation [36];

  MTX_Identity33_();
  MTX_Identity33_(rotation);
  MTX_RotX33_
            (rotation,(int)*(short *)(&data_02053580 + (xAngle >> 4) * 2),
             (int)*(short *)(&data_02053580 + (0x400U - (xAngle >> 4) & 0xfff) * 2));
  MTX_Concat33(matrix,rotation,matrix);
  MTX_Identity33_(rotation);
  MTX_RotY33_(rotation,(int)*(short *)(&data_02053580 + (yAngle >> 4) * 2),
                      (int)*(short *)(&data_02053580 + (0x400U - (yAngle >> 4) & 0xfff) * 2))
  ;
  MTX_Concat33(matrix,rotation,matrix);
  MTX_Identity33_(rotation);
  MTX_RotZ33_(rotation,(int)*(short *)(&data_02053580 + (zAngle >> 4) * 2),
                      (int)*(short *)(&data_02053580 + (0x400U - (zAngle >> 4) & 0xfff) * 2))
  ;
  MTX_Concat33(matrix,rotation,matrix);
}

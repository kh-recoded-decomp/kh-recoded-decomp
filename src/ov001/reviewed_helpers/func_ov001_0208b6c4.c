#include "nitro/types.h"

extern unsigned int *data_ov001_020a04f4;
extern unsigned char data_0205356c;
extern unsigned int EvaluateInterpolationCurve_02025718();
extern unsigned int func_020257b0();

void func_ov001_0208b6c4(void) {
  int *work;
  int angle;

  work = data_ov001_020a04f4;
  data_ov001_020a04f4[0x24] = data_ov001_020a04f4[0x24] + -1;
  if (work[0x24] == 0) {
    work[0x26] = 0;
    angle = work[0x21];
  }
  else {
    angle = EvaluateInterpolationCurve_02025718(3,work[0x25],work[0x24]);
    angle = func_020257b0(angle,work[0x21],work[0x23]);
  }
  *work = (int)*(short *)(&data_0205356c + (angle >> 4) * 2);
  work[1] = (int)*(short *)(&data_0205356c + (0x400U - (angle >> 4) & 0xfff) * 2);
}

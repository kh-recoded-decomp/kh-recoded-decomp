#include "nitro/types.h"

extern unsigned int *data_ov001_020a0514;
extern unsigned char data_02053580;
extern unsigned int EvaluateInterpolationCurve();
extern unsigned int ScaleAroundPivot();

void func_ov001_0208b6ec(void) {
  int *work;
  int angle;

  work = data_ov001_020a0514;
  data_ov001_020a0514[0x24] = data_ov001_020a0514[0x24] + -1;
  if (work[0x24] == 0) {
    work[0x26] = 0;
    angle = work[0x21];
  }
  else {
    angle = EvaluateInterpolationCurve(3,work[0x25],work[0x24]);
    angle = ScaleAroundPivot(angle,work[0x21],work[0x23]);
  }
  *work = (int)*(short *)(&data_02053580 + (angle >> 4) * 2);
  work[1] = (int)*(short *)(&data_02053580 + (0x400U - (angle >> 4) & 0xfff) * 2);
}

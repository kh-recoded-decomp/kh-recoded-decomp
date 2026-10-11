#include "nitro/types.h"

extern unsigned int *gActorChannelContext;
extern unsigned char gSinFx12Table;
extern unsigned int EvaluateInterpolationCurve();
extern unsigned int ScaleAroundPivot();

void func_ov001_0208b6ec(void) {
  int *work;
  int angle;

  work = gActorChannelContext;
  gActorChannelContext[0x24] = gActorChannelContext[0x24] + -1;
  if (work[0x24] == 0) {
    work[0x26] = 0;
    angle = work[0x21];
  }
  else {
    angle = EvaluateInterpolationCurve(3,work[0x25],work[0x24]);
    angle = ScaleAroundPivot(angle,work[0x21],work[0x23]);
  }
  *work = (int)*(short *)(&gSinFx12Table + (angle >> 4) * 2);
  work[1] = (int)*(short *)(&gSinFx12Table + (0x400U - (angle >> 4) & 0xfff) * 2);
}

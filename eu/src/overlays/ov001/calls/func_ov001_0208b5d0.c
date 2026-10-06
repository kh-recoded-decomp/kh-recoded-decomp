#include "nitro/types.h"

extern unsigned int *data_ov001_020a0514;
extern unsigned int EvaluateInterpolationCurve();
extern unsigned int VEC_MultAdd();
extern unsigned int VEC_Subtract();
extern unsigned int MI_CpuCopy8();
extern unsigned int ScaleAroundPivot();

void func_ov001_0208b5d0(void) {
  unsigned int *work;
  int scale;
  unsigned int value;
  u8 delta [12];

  work = data_ov001_020a0514;
  data_ov001_020a0514[0x24] = data_ov001_020a0514[0x24] + -1;
  if (work[0x24] == 0) {
    MI_CpuCopy8(work + 0x67,work,0x38);
    work[0x26] = 0;
    return;
  }
  scale = EvaluateInterpolationCurve(5,work[0x25],work[0x24]);
  value = ScaleAroundPivot(scale,work[0x67],work[0x54]);
  *work = value;
  value = ScaleAroundPivot(scale,work[0x68],work[0x55]);
  work[1] = value;
  value = ScaleAroundPivot(scale,work[0x69],work[0x56]);
  work[2] = value;
  value = ScaleAroundPivot(scale,work[0x6a],work[0x57]);
  work[3] = value;
  value = ScaleAroundPivot(scale,work[0x6b],work[0x58]);
  work[4] = value;
  VEC_Subtract(work + 0x6c,work + 0x59,delta);
  VEC_MultAdd(scale,delta,work + 0x59,work + 5);
  VEC_Subtract(work + 0x6f,work + 0x5c,delta);
  VEC_MultAdd(scale,delta,work + 0x5c,work + 8);
  VEC_Subtract(work + 0x72,work + 0x5f,delta);
  VEC_MultAdd(scale,delta,work + 0x5f,work + 0xb);
}

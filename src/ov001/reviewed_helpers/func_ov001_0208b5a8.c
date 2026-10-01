#include "nitro/types.h"

extern unsigned int *data_ov001_020a04f4;
extern unsigned int EvaluateInterpolationCurve_02025718();
extern unsigned int VEC_MultAdd_01ffa09c();
extern unsigned int VEC_Subtract_01ff9e3c();
extern unsigned int func_01ff89a8();
extern unsigned int func_020257b0();

void func_ov001_0208b5a8(void) {
  unsigned int *work;
  int scale;
  unsigned int value;
  u8 delta [12];

  work = data_ov001_020a04f4;
  data_ov001_020a04f4[0x24] = data_ov001_020a04f4[0x24] + -1;
  if (work[0x24] == 0) {
    func_01ff89a8(work + 0x67,work,0x38);
    work[0x26] = 0;
    return;
  }
  scale = EvaluateInterpolationCurve_02025718(5,work[0x25],work[0x24]);
  value = func_020257b0(scale,work[0x67],work[0x54]);
  *work = value;
  value = func_020257b0(scale,work[0x68],work[0x55]);
  work[1] = value;
  value = func_020257b0(scale,work[0x69],work[0x56]);
  work[2] = value;
  value = func_020257b0(scale,work[0x6a],work[0x57]);
  work[3] = value;
  value = func_020257b0(scale,work[0x6b],work[0x58]);
  work[4] = value;
  VEC_Subtract_01ff9e3c(work + 0x6c,work + 0x59,delta);
  VEC_MultAdd_01ffa09c(scale,delta,work + 0x59,work + 5);
  VEC_Subtract_01ff9e3c(work + 0x6f,work + 0x5c,delta);
  VEC_MultAdd_01ffa09c(scale,delta,work + 0x5c,work + 8);
  VEC_Subtract_01ff9e3c(work + 0x72,work + 0x5f,delta);
  VEC_MultAdd_01ffa09c(scale,delta,work + 0x5f,work + 0xb);
}

#include "nitro/types.h"

extern unsigned int *data_ov002_0206c46c;
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int NNSi_FndFreeFromDefaultHeap();
extern unsigned int MI_CpuFill8();

void func_ov002_020666c8(unsigned int value) {
  if (data_ov002_0206c46c != (void *)0x0) {
    NNSi_FndFreeFromDefaultHeap(data_ov002_0206c46c);
    data_ov002_0206c46c = (void *)0x0;
  }
  data_ov002_0206c46c = NNSi_FndAllocFromDefaultHeap(0x2c);
  MI_CpuFill8(data_ov002_0206c46c,0,0x2c);
  *data_ov002_0206c46c = value;
}

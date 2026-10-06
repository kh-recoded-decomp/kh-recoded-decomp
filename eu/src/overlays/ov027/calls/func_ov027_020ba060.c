#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov027_020ba124();
extern unsigned int data_ov027_020ba3e4;
extern unsigned int NNSi_FndGetCurrentRootHeap();
extern unsigned int MI_CpuFill8();
extern unsigned int NNS_FndInitList();

code * func_ov027_020ba060(void) {
  void *work;

  work = NNSi_FndGetCurrentRootHeap();
  data_ov027_020ba3e4 = work;
  MI_CpuFill8(work,0,0x18);
  NNS_FndInitList(work,0x18);
  NNS_FndInitList((int)work + 0xc,0x18);
  return func_ov027_020ba124;
}

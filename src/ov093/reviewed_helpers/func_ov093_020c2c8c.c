#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov093_020c2d80();
extern unsigned int data_ov093_020c50e4;
extern unsigned int GetBgDataFromArchive_0202b554();
extern unsigned int NNSi_FndGetCurrentRootHeap_0202a764();
extern unsigned int func_0202c478();

code * func_ov093_020c2c8c(unsigned int *initialValues) {
  u32 resource;

  data_ov093_020c50e4 = NNSi_FndGetCurrentRootHeap_0202a764();
  *(unsigned int *)((int)data_ov093_020c50e4 + 4) = *initialValues;
  *(unsigned int *)((int)data_ov093_020c50e4 + 8) = initialValues[1];
  *(unsigned int *)((int)data_ov093_020c50e4 + 0xc) = initialValues[2];
  resource = initialValues[3];
  *(u32 *)((int)data_ov093_020c50e4 + 0x10) = resource;
  *(unsigned int *)((int)data_ov093_020c50e4 + 0x1c) = 0;
  *(unsigned int *)((int)data_ov093_020c50e4 + 0x26c) = 0;
  resource = func_0202c478((*(int *)((int)data_ov093_020c50e4 + 4) + 0x8000U & 0xfffffc) << 7 |
                              0x80000001,0xe,0xfffffc,resource);
  *(u32 *)((int)data_ov093_020c50e4 + 0x1c) = resource;
  GetBgDataFromArchive_0202b554
            ((void *)((int)data_ov093_020c50e4 + 0x20),*(void **)((int)data_ov093_020c50e4 + 0x1c)
             ,0,0,0);
  return func_ov093_020c2d80;
}

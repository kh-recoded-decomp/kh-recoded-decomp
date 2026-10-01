#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov091_020c194c();
extern unsigned int data_ov091_020c373c;
extern unsigned int GetBgDataFromArchive_0202b554();
extern unsigned int NNSi_FndGetCurrentRootHeap_0202a764();
extern unsigned int func_0202c478();

code * func_ov091_020c1858(unsigned int *initialValues) {
  u32 resource;

  data_ov091_020c373c = NNSi_FndGetCurrentRootHeap_0202a764();
  *(unsigned int *)((int)data_ov091_020c373c + 4) = *initialValues;
  *(unsigned int *)((int)data_ov091_020c373c + 8) = initialValues[1];
  *(unsigned int *)((int)data_ov091_020c373c + 0xc) = initialValues[2];
  resource = initialValues[3];
  *(u32 *)((int)data_ov091_020c373c + 0x10) = resource;
  *(unsigned int *)((int)data_ov091_020c373c + 0x1c) = 0;
  *(unsigned int *)((int)data_ov091_020c373c + 0x26c) = 0;
  resource = func_0202c478((*(int *)((int)data_ov091_020c373c + 4) + 0x8000U & 0xfffffc) << 7 |
                              0x80000003,0xe,0xfffffc,resource);
  *(u32 *)((int)data_ov091_020c373c + 0x1c) = resource;
  GetBgDataFromArchive_0202b554
            ((void *)((int)data_ov091_020c373c + 0x20),*(void **)((int)data_ov091_020c373c + 0x1c)
             ,0,0,0);
  return func_ov091_020c194c;
}

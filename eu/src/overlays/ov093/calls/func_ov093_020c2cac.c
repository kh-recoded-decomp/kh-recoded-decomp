#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdatePopupManager_020c2da0();
extern unsigned int data_ov093_020c5104;
extern unsigned int GetBgDataFromArchive();
extern unsigned int NNSi_FndGetCurrentRootHeap();
extern unsigned int Archive_LoadFile();

code * func_ov093_020c2cac(unsigned int *initialValues) {
  u32 resource;

  data_ov093_020c5104 = NNSi_FndGetCurrentRootHeap();
  *(unsigned int *)((int)data_ov093_020c5104 + 4) = *initialValues;
  *(unsigned int *)((int)data_ov093_020c5104 + 8) = initialValues[1];
  *(unsigned int *)((int)data_ov093_020c5104 + 0xc) = initialValues[2];
  resource = initialValues[3];
  *(u32 *)((int)data_ov093_020c5104 + 0x10) = resource;
  *(unsigned int *)((int)data_ov093_020c5104 + 0x1c) = 0;
  *(unsigned int *)((int)data_ov093_020c5104 + 0x26c) = 0;
  resource = Archive_LoadFile((*(int *)((int)data_ov093_020c5104 + 4) + 0x8000U & 0xfffffc) << 7 |
                              0x80000001,0xe,0xfffffc,resource);
  *(u32 *)((int)data_ov093_020c5104 + 0x1c) = resource;
  GetBgDataFromArchive
            ((void *)((int)data_ov093_020c5104 + 0x20),*(void **)((int)data_ov093_020c5104 + 0x1c)
             ,0,0,0);
  return UpdatePopupManager_020c2da0;
}

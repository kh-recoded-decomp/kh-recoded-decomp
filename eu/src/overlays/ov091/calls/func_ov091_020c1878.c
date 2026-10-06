#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdatePopupManager();
extern unsigned int data_ov091_020c375c;
extern unsigned int GetBgDataFromArchive();
extern unsigned int NNSi_FndGetCurrentRootHeap();
extern unsigned int Archive_LoadFile();

code * func_ov091_020c1878(unsigned int *initialValues) {
  u32 resource;

  data_ov091_020c375c = NNSi_FndGetCurrentRootHeap();
  *(unsigned int *)((int)data_ov091_020c375c + 4) = *initialValues;
  *(unsigned int *)((int)data_ov091_020c375c + 8) = initialValues[1];
  *(unsigned int *)((int)data_ov091_020c375c + 0xc) = initialValues[2];
  resource = initialValues[3];
  *(u32 *)((int)data_ov091_020c375c + 0x10) = resource;
  *(unsigned int *)((int)data_ov091_020c375c + 0x1c) = 0;
  *(unsigned int *)((int)data_ov091_020c375c + 0x26c) = 0;
  resource = Archive_LoadFile((*(int *)((int)data_ov091_020c375c + 4) + 0x8000U & 0xfffffc) << 7 |
                              0x80000003,0xe,0xfffffc,resource);
  *(u32 *)((int)data_ov091_020c375c + 0x1c) = resource;
  GetBgDataFromArchive
            ((void *)((int)data_ov091_020c375c + 0x20),*(void **)((int)data_ov091_020c375c + 0x1c)
             ,0,0,0);
  return UpdatePopupManager;
}

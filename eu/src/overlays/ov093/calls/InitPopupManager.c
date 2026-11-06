#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdatePopupManager_020c2da0();
extern unsigned int gTrophyPopupWorkStorage;
extern unsigned int GetBgDataFromArchive();
extern unsigned int GetRunningTaskWork();
extern unsigned int Archive_LoadFile();

code * InitPopupManager(unsigned int *initialValues) {
  u32 resource;

  gTrophyPopupWorkStorage = GetRunningTaskWork();
  *(unsigned int *)((int)gTrophyPopupWorkStorage + 4) = *initialValues;
  *(unsigned int *)((int)gTrophyPopupWorkStorage + 8) = initialValues[1];
  *(unsigned int *)((int)gTrophyPopupWorkStorage + 0xc) = initialValues[2];
  resource = initialValues[3];
  *(u32 *)((int)gTrophyPopupWorkStorage + 0x10) = resource;
  *(unsigned int *)((int)gTrophyPopupWorkStorage + 0x1c) = 0;
  *(unsigned int *)((int)gTrophyPopupWorkStorage + 0x26c) = 0;
  resource = Archive_LoadFile((*(int *)((int)gTrophyPopupWorkStorage + 4) + 0x8000U & 0xfffffc) << 7 |
                              0x80000001,0xe,0xfffffc,resource);
  *(u32 *)((int)gTrophyPopupWorkStorage + 0x1c) = resource;
  GetBgDataFromArchive
            ((void *)((int)gTrophyPopupWorkStorage + 0x20),*(void **)((int)gTrophyPopupWorkStorage + 0x1c)
             ,0,0,0);
  return UpdatePopupManager_020c2da0;
}

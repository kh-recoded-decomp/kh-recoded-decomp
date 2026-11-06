#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdatePopupManager();
extern unsigned int gReportTopPopupWork;
extern unsigned int GetBgDataFromArchive();
extern unsigned int GetRunningTaskWork();
extern unsigned int Archive_LoadFile();

code * ReportTopPopup_InitTaskWork(unsigned int *initialValues) {
  u32 resource;

  gReportTopPopupWork = GetRunningTaskWork();
  *(unsigned int *)((int)gReportTopPopupWork + 4) = *initialValues;
  *(unsigned int *)((int)gReportTopPopupWork + 8) = initialValues[1];
  *(unsigned int *)((int)gReportTopPopupWork + 0xc) = initialValues[2];
  resource = initialValues[3];
  *(u32 *)((int)gReportTopPopupWork + 0x10) = resource;
  *(unsigned int *)((int)gReportTopPopupWork + 0x1c) = 0;
  *(unsigned int *)((int)gReportTopPopupWork + 0x26c) = 0;
  resource = Archive_LoadFile((*(int *)((int)gReportTopPopupWork + 4) + 0x8000U & 0xfffffc) << 7 |
                              0x80000003,0xe,0xfffffc,resource);
  *(u32 *)((int)gReportTopPopupWork + 0x1c) = resource;
  GetBgDataFromArchive
            ((void *)((int)gReportTopPopupWork + 0x20),*(void **)((int)gReportTopPopupWork + 0x1c)
             ,0,0,0);
  return UpdatePopupManager;
}

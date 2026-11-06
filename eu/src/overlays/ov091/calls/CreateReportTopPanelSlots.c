#include "nitro/types.h"

extern unsigned char gReportTopUpperPanelLayouts;
extern unsigned int gReportTopLowerPanelLayout;
extern unsigned int InitObjManager();
extern unsigned int PXI_Init_0204f020();
extern unsigned int CreateListPanelSlot();

void CreateReportTopPanelSlots(int work) {
  int index;
  u32 configuration [4];

  index = 0;
  configuration[0] = (*(int *)(work + 4) + 0x8000U & 0xfffffc) << 7 | 0x80000007;
  configuration[1] = 1;
  configuration[2] = 0;
  configuration[3] = 0;
  InitObjManager(work + 0xf4,configuration);
  PXI_Init_0204f020(work + 0xf4,
                      (*(int *)(work + 0xc) + 0x8000U & 0xfffffc) << 7 | 0x80000000);
  do {
    CreateListPanelSlot(0,index,&gReportTopUpperPanelLayouts + index * 0x18,work);
    index = index + 1;
  } while (index < 6);
  configuration[0] = (*(int *)(work + 4) + 0x8000U & 0xfffffc) << 7 | 0x80000004;
  configuration[1] = 2;
  configuration[2] = 0;
  configuration[3] = 0;
  InitObjManager(work + 0x6528,configuration);
  CreateListPanelSlot(1,0,&gReportTopLowerPanelLayout,work);
}

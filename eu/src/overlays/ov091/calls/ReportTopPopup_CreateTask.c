#include "nitro/types.h"

extern unsigned int *gReportTopPopupWork;
extern unsigned char gReportTopSummaryPopupFlagTables;
extern unsigned int CreateTaskObject();

unsigned int ReportTopPopup_CreateTask(void *initialValues) {
  void *instance;

  instance = CreateTaskObject(&gReportTopSummaryPopupFlagTables + 0x0c,initialValues);
  *gReportTopPopupWork = instance;
  return *gReportTopPopupWork;
}

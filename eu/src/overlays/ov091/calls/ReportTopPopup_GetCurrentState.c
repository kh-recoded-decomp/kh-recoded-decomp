#include "nitro/types.h"

extern u32 gReportTopPopupWork;
extern u32 ReportTopPopup_GetState();

void ReportTopPopup_GetCurrentState(void) {
  ReportTopPopup_GetState(gReportTopPopupWork + 44);
}

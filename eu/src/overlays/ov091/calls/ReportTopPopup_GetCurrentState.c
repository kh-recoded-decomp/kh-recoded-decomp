#include "nitro/types.h"

extern u32 data_ov091_020c375c;
extern u32 ReportTopPopup_GetState();

void ReportTopPopup_GetCurrentState(void) {
  ReportTopPopup_GetState(data_ov091_020c375c + 44);
}

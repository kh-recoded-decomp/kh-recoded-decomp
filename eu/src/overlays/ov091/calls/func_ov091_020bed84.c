#include "nitro/types.h"

typedef unsigned int code();

extern unsigned char gReportTopStateHandlers;
extern unsigned int DrawRecordSummaryText();
extern unsigned int ResetListCursor_020bf8cc();
extern unsigned int func_ov091_020c1774();

void func_ov091_020bed84(unsigned int work) {
  int state;

  state = func_ov091_020c1774();
  if (*(code **)(&gReportTopStateHandlers + state * 4) != (code *)0x0) {
    (**(code **)(&gReportTopStateHandlers + state * 4))(work);
  }
  DrawRecordSummaryText(work);
  ResetListCursor_020bf8cc(work);
}

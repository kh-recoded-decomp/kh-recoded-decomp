#include "nitro/types.h"

extern void ReportTop_HandleState0Noop(void);
extern void RequestEntryTransitionIfIdle(void); /* RequestEntryTransitionIfIdle */
extern void RunIntroPopupStep(void);

void (*const gReportTopStateHandlers[3])(void) = {
    ReportTop_HandleState0Noop,
    RequestEntryTransitionIfIdle, /* RequestEntryTransitionIfIdle */
    RunIntroPopupStep,
};

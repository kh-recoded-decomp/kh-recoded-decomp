#include "nitro/types.h"

extern void func_ov097_020c159c(void);
extern void TickEntryTransition(void);

void (*const gStoryReportStateHandlers[2])(void) = {
    func_ov097_020c159c,
    TickEntryTransition,
};

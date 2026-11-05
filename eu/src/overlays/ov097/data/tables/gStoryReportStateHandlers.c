#include "nitro/types.h"

extern void StoryReport_HandleState0Noop(void);
extern void TickEntryTransition(void);

void (*const gStoryReportStateHandlers[2])(void) = {
    StoryReport_HandleState0Noop,
    TickEntryTransition,
};

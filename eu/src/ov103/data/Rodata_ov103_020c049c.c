#include "nitro/types.h"

extern void RunFadeInStep(void);
extern void TheaterReport_HandleState0Noop(void);
extern void InitTheaterReportScreen(void);
extern void InitTheaterReportSlotPoolThunk(void);

void *const gTheaterReportStateHandlers[4] = {
    (void *)TheaterReport_HandleState0Noop,
    (void *)InitTheaterReportScreen,
    (void *)RunFadeInStep,
    (void *)InitTheaterReportSlotPoolThunk,
};

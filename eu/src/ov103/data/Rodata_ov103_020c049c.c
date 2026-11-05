#include "nitro/types.h"

extern void RunFadeInStep(void);
extern void TheaterReport_HandleState0Noop(void);
extern void InitTheaterReportScreen(void);
extern void InitTheaterReportSlotPoolThunk(void);

void *const data_ov103_020c049c[4] = {
    (void *)TheaterReport_HandleState0Noop,
    (void *)InitTheaterReportScreen,
    (void *)RunFadeInStep,
    (void *)InitTheaterReportSlotPoolThunk,
};

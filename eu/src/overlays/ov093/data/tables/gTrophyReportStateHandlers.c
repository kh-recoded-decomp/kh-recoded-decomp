#include "nitro/types.h"

extern void TrophyReport_HandleState0Noop(void);
extern void WaitForBrightnessReset(void); /* WaitForBrightnessReset */
extern void RunEntryUnlockSequence(void);
extern void RunRewardUnlockSequence(void);
extern void RunUnlockSequence(void);
extern void RunPrizeMessageSequence(void);
extern void TrophyReport_HandleState6Noop(void);

void (*const gTrophyReportStateHandlers[7])(void) = {
    TrophyReport_HandleState0Noop,
    WaitForBrightnessReset, /* WaitForBrightnessReset */
    RunEntryUnlockSequence,
    RunRewardUnlockSequence,
    RunUnlockSequence,
    RunPrizeMessageSequence,
    TrophyReport_HandleState6Noop,
};

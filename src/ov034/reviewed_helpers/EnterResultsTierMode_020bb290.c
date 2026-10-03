#include "nitro/types.h"

typedef struct ResultsParams {
    u8 pad_00[0x8c];
    s32 isBonusStage;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[0x6bbc];
    s32 tierThresholds[3];
    u8 pad_6bc8[0x30];
    s32 tierIndex;
    u8 pad_6bfc[0x188];
    s32 tierTimer;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen g_resultsScreen_020c0f80;
extern void SetResultsMode_020bb274(u32 mode);

void EnterResultsTierMode_020bb290(u32 mode)
{
    SetResultsMode_020bb274(mode);
    g_resultsScreen_020c0f80.work->tierIndex = 0;
    if (g_resultsScreen_020c0f80.params->isBonusStage != 0) {
        g_resultsScreen_020c0f80.work->tierThresholds[2] = 100;
        g_resultsScreen_020c0f80.work->tierThresholds[1] = g_resultsScreen_020c0f80.work->tierThresholds[2];
        g_resultsScreen_020c0f80.work->tierThresholds[0] = g_resultsScreen_020c0f80.work->tierThresholds[1];
    } else {
        g_resultsScreen_020c0f80.work->tierThresholds[0] = 10;
        g_resultsScreen_020c0f80.work->tierThresholds[1] = 30;
        g_resultsScreen_020c0f80.work->tierThresholds[2] = 50;
    }
    g_resultsScreen_020c0f80.work->tierTimer = 0;
}

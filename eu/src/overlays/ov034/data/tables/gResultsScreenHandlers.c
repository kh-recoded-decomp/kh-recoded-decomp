#include "src/overlays/ov034/ResultsScreen.h"

extern u32 StartResultsScreen(void);
extern u32 PollResultsScreen(void);
extern u32 FinishResultsScreen(void);

ResultsStateHandler gResultsScreenHandlers[4] = {
    StartResultsScreen,
    PollResultsScreen,
    FinishResultsScreen,
    ResultsScreenIdle,
};

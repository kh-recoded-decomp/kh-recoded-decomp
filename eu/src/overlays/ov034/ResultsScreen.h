#ifndef KH_RECODED_RESULTS_SCREEN_H
#define KH_RECODED_RESULTS_SCREEN_H

#include "ov034/ResultsScreen.h"

extern ResultsUpdateScreen data_ov034_020c0fa0;
extern ResultsStateHandler gResultsScreenHandlers[4];
u32 ResultsScreenIdle(void);
int UpdateResultsScreen(void);

#endif

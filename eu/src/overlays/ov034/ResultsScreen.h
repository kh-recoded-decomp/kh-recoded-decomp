#ifndef KH_RECODED_RESULTS_SCREEN_H
#define KH_RECODED_RESULTS_SCREEN_H

#include "../include/ov034/ResultsScreen.h"

extern ResultsUpdateScreen gResultsScreenPointersPrefix;
extern ResultsStateHandler gResultsScreenHandlers[4];
u32 ResultsScreenIdle(void);
int UpdateResultsScreen(void);

#endif

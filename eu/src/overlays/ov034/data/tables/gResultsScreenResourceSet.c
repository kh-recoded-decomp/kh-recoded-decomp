#include "nitro/types.h"

extern u8 gResultsRankMarkAlphaText[];
extern u8 gResultsRankMarkBetaText[];
extern u8 gResultsRankMarkGammaText[];

void *gResultsRankMarkTexts[3] = {
    gResultsRankMarkAlphaText,
    gResultsRankMarkBetaText,
    gResultsRankMarkGammaText,
};

#include "nitro/types.h"

extern void FinishResultsScreen_020bdc3c(void);
extern void Gfd_DefaultFreeTexVram_020bdc8c(void);
extern void PollResultsScreen_020bdc18(void);
extern void StartResultsScreen_020bdbd0(void);

void (*data_ov034_020be924[4])(void) = {
    StartResultsScreen_020bdbd0,
    PollResultsScreen_020bdc18,
    FinishResultsScreen_020bdc3c,
    Gfd_DefaultFreeTexVram_020bdc8c,
};

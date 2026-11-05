#include "nitro/types.h"

extern void BeginResumeMode(void); /* BeginResumeMode */
extern void UpdateResumeMenuUntilResult(void);
extern void FinishResumeMenuAndRestoreField(void);
extern void ResumeModeStateHold(void);

void (*gResumeModeHandlers[4])(void) = {
    BeginResumeMode,
    UpdateResumeMenuUntilResult,
    FinishResumeMenuAndRestoreField,
    ResumeModeStateHold,
};

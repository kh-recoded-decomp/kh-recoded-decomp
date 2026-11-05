#include "nitro/types.h"

extern void ResetFieldEntryWaitTimer(void); /* Word_Clear */
extern void ComputePool1Progress(void); /* ComputePool1Progress */
extern void ComputePool2Target(void); /* ComputePool2Target */
extern void CopyPool3Entry(void); /* CopyPool3Entry */
extern void ResetFallTarget(void); /* ResetFallTarget */
extern void ProcessFieldFallResetRequest(void);

void (*const gPoolValueHandlers[5])(void) = {
    ResetFieldEntryWaitTimer, /* Word_Clear */
    ComputePool1Progress, /* ComputePool1Progress */
    ComputePool2Target, /* ComputePool2Target */
    CopyPool3Entry, /* CopyPool3Entry */
    ResetFallTarget, /* ResetFallTarget */
};

void (*const gPoolInitHandlers[4])(void) = {
    ProcessFieldFallResetRequest,
    NULL,
    NULL,
    NULL,
};

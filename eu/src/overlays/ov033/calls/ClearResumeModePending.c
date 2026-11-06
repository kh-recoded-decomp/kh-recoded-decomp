#include "nitro/types.h"

typedef struct ResumeModeState {
    u8 pad_00[0x0c];
    u32 pending;
} ResumeModeState;

extern ResumeModeState *gResumeModeWorkStorage;

void ClearResumeModePending(void)
{
    gResumeModeWorkStorage->pending = FALSE;
}

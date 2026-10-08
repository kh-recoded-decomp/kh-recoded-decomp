#include "nitro/types.h"

typedef struct ResumeModeState {
    u8 pad_00[0x0c];
    u32 pending;
} ResumeModeState;

extern ResumeModeState *data_ov033_020baae0;

void ClearResumeModePending(void)
{
    data_ov033_020baae0->pending = FALSE;
}

#include "nitro/types.h"

typedef struct EventState {
    u8 pad_0000[0xca34];
    u32 flagCa34;
} EventState;

extern EventState *data_ov039_020bea20;

void SetEventStateFlagCa34(void)
{
    data_ov039_020bea20->flagCa34 = TRUE;
}

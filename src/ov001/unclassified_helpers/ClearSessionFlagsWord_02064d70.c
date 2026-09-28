#include "nitro/types.h"

extern u32 data_ov001_020a0460;

void ClearSessionFlagsWord_02064d70(void)
{
    *(s16 *)(data_ov001_020a0460 + 0x20e) = ~2;
}

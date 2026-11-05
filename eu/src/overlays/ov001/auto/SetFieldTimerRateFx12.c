#include "nitro/types.h"

extern u8 *data_ov001_020a0494;

void SetFieldTimerRateFx12(u16 value)
{
    *(u16 *)(data_ov001_020a0494 + 0x22) = value;
}

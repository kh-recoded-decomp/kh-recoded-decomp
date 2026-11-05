#include "nitro/types.h"

extern u8 *data_ov001_020a04e8;

void SetSubsceneBgSetupCallback(u32 value)
{
    *(u32 *)(data_ov001_020a04e8 + 0x2c) = value;
}

#include "nitro/types.h"

extern u16 data_02060500;

BOOL IsButtonBPressed_020632c8(void)
{
    return (data_02060500 & 2) != 0;
}

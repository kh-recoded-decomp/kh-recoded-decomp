#include "nitro/types.h"

extern u16 data_02060500;

BOOL IsButtonYPressed_02063300(void)
{
    return (data_02060500 & 0x800) != 0;
}

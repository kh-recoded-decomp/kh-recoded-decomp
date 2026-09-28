#include "nitro/types.h"

typedef enum {
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
} PMLCDPower;

extern PMLCDPower PM_GetLCDPower_02010a08(void);
extern u32 PMi_SendChannelValueSync_02010448(u32 channel, u16 value, u32 reserved);

u32 PMi_SetAmp_020105a8(u32 status)
{
    if (PM_GetLCDPower_02010a08() != 0) {
        return PMi_SendChannelValueSync_02010448(0x10, status, 0);
    }

    return 0;
}

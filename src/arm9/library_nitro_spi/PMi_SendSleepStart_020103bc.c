#include "nitro/types.h"

extern void PMi_SendPxiCommandArraySync_02010350(u32 *words, int count);
extern BOOL PMi_SetLCDPower_020108a0(int sw, int led, BOOL skip, BOOL isSync);

u32 PMi_SendSleepStart_020103bc(u16 trigger, u16 keyIntrData)
{
    u32 command[2];

    command[0] = 0x03006000;
    PMi_SendPxiCommandArraySync_02010350(command, 1);

    while (PMi_SetLCDPower_020108a0(0, 2, FALSE, TRUE) != TRUE) {
    }

    command[0] = (trigger & 0xff) | 0x02006200;
    command[1] = (keyIntrData & 0xffff) | 0x01010000;
    PMi_SendPxiCommandArraySync_02010350(command, 2);

    return 0;
}

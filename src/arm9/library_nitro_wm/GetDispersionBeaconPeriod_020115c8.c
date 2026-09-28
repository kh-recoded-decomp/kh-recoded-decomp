#include "nitro/types.h"

extern void func_02004ac8(u8 *macAddress);
extern unsigned long long func_02023dbc(u32 numerator, u32 denominator);
extern u32 data_02fffc3c;

u16 GetDispersionBeaconPeriod_020115c8(void)
{
    u8 mac[6];
    u16 sum;
    int i;
    u32 remainder;

    func_02004ac8(mac);

    i = 0;
    sum = 0;
    do {
        u8 byte = mac[i];
        i++;
        sum = sum + byte;
    } while (i < 6);

    sum = sum + (u16)data_02fffc3c;
    remainder = (u32)(func_02023dbc((u16)(sum * 7), 20) >> 32);

    return (u16)(remainder + 200);
}

#include "nitro/types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern int TP_GetLatestIndexInAuto_0200ff50(void);
extern void func_020100e0(TouchSample *out, TouchSample *raw);
extern void func_01ff89a8(const void *src, void *dst, u32 len);
extern TouchSample data_02060534[];

int CopyRecentTouchPoints_0202b618(TouchSample *table)
{
    int latest;
    int i;
    s16 count = 0;

    if (!((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15)) {
        TouchSample point;

        latest = TP_GetLatestIndexInAuto_0200ff50();
        i = 0;
        latest -= 3;

        for (; i < 4; i++) {
            int index = latest + i;
            TouchSample *sample;

            if (index < 0) {
                index += 5;
            }
            sample = &data_02060534[index];
            if (sample->touch != 0 && sample->validity == 0) {
                func_020100e0(&point, sample);
                if (point.x <= 0xff && point.y <= 0xbf) {
                    func_01ff89a8(&point, &table[count++], 8);
                }
            }
        }
    }

    return count;
}

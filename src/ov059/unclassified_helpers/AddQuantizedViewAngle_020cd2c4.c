#include "nitro/types.h"

extern int func_ov021_020af84c(void);
extern s32 func_02023dbc(s32 numerator, s32 denominator);

u16 AddQuantizedViewAngle_020cd2c4(u16 angle)
{
    int viewAngle = (s16)func_ov021_020af84c();
    s8 sign = (viewAngle == 0) ? 0 : ((viewAngle > 0) ? 1 : -1);
    int magnitude = viewAngle;

    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude < 0x3fff) {
        return angle + (u16)(func_02023dbc(sign * (magnitude + 0x80), 0x1fff) * 0x1fff);
    }
    return angle + (u16)(func_02023dbc(sign * (magnitude + 0x107f), 0x1fff) * 0x1fff);
}

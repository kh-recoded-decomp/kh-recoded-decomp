/* Shared US RGB555 interpolation; also byte-exact for this EU copy. */
#include "nitro/types.h"

extern int _s32_div_f(int numerator, int denominator);

u16 LerpColor555(u16 fromColor, u16 toColor, int step, u16 stepCount)
{
    int fromRed = (s16)(fromColor & 0x1f);
    int fromGreen = (s16)((fromColor & 0x3e0) >> 5);
    int fromBlue = (s16)((fromColor & 0x7c00) >> 10);
    int toBlue = (s16)((toColor & 0x7c00) >> 10);
    int blueDelta = _s32_div_f(step * (toBlue - fromBlue), stepCount);
    int toRed = (s16)(toColor & 0x1f);
    int redDelta = _s32_div_f(step * (toRed - fromRed), stepCount);
    int toGreen = (s16)((toColor & 0x3e0) >> 5);
    int greenDelta = _s32_div_f(step * (toGreen - fromGreen), stepCount);
    s16 red = fromRed + redDelta;
    s16 green = fromGreen + greenDelta;
    s16 blue = fromBlue + blueDelta;

    return (red << 0) | (green << 5) | (blue << 10);
}

#include "nitro/types.h"

extern int func_02023dbc(int numerator, int denominator);

u16 LerpColor555_02076e30(u16 fromColor, u16 toColor, int step, u16 stepCount)
{
    int fromRed = (s16)(fromColor & 0x1f);
    int fromGreen = (s16)((fromColor & 0x3e0) >> 5);
    int fromBlue = (s16)((fromColor & 0x7c00) >> 10);
    int toBlue = (s16)((toColor & 0x7c00) >> 10);
    int blueDelta = func_02023dbc(step * (toBlue - fromBlue), stepCount);
    int toRed = (s16)(toColor & 0x1f);
    int redDelta = func_02023dbc(step * (toRed - fromRed), stepCount);
    int toGreen = (s16)((toColor & 0x3e0) >> 5);
    int greenDelta = func_02023dbc(step * (toGreen - fromGreen), stepCount);
    s16 red = fromRed + redDelta;
    s16 green = fromGreen + greenDelta;
    s16 blue = fromBlue + blueDelta;

    return (red << 0) | (green << 5) | (blue << 10);
}

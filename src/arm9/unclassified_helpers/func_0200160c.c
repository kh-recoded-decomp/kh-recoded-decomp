#include "nitro/types.h"

extern int func_02001908(int context, int value, int *remaining);
extern void func_02001490(int *context, u32 value);
extern void func_020015a0(int *context, u32 x, u32 y, u32 color, u32 flags, u32 value);

void func_0200160c(int *context, u32 x, u32 y, u32 color, u32 flags, int value,
                    u32 overrideValue, int maxWidth)
{
    int remaining;
    int width;
    int maxSeen;
    u32 savedField;

    remaining = value;
    savedField = *context;
    maxSeen = 0;
    do {
        width = func_02001908(context, remaining, &remaining);
        if (maxSeen < width) {
            maxSeen = width;
        }
    } while (remaining != 0);
    if (maxSeen > maxWidth) {
        func_02001490(context, overrideValue);
    }
    func_020015a0(context, x, y, color, flags, value);
    func_02001490(context, savedField);
}

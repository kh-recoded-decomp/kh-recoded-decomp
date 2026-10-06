#include "nitro/types.h"

extern int func_ov022_020a8d00(void);

int func_ov022_020a8ef8(int context, int minWidth)
{
    int width = func_ov022_020a8d00();

    *(s32 *)(context + 0x58) = 0;
    if (width <= minWidth) {
        width = minWidth;
    }
    return width;
}

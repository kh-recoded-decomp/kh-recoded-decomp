#include "nitro/types.h"

extern int func_ov022_020a8ce0(void);

int func_ov022_020a8ed8(int context, int minWidth)
{
    int width = func_ov022_020a8ce0();

    *(s32 *)(context + 0x58) = 0;
    if (width <= minWidth) {
        width = minWidth;
    }
    return width;
}

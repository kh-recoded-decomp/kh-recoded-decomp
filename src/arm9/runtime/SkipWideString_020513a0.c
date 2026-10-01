#include "nitro/types.h"

u16 *SkipWideString_020513a0(u16 *text)
{
    while (*text != 0) {
        text++;
    }
    return text + 1;
}

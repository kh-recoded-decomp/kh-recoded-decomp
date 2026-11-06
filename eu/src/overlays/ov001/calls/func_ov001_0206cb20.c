#include "nitro/types.h"

extern u32 gFieldMessageSpriteManager;

BOOL func_ov001_0206cb20(void)
{
    if (*(char *)(gFieldMessageSpriteManager + 0x15) == 1) {
        return 1;
    }
    return 0;
}

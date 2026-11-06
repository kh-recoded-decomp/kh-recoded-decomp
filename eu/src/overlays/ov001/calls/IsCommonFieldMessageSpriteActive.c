#include "nitro/types.h"

extern u32 gFieldMessageSpriteManager;

BOOL IsCommonFieldMessageSpriteActive(void)
{
    if (*(char *)(gFieldMessageSpriteManager + 0x15) == 1) {
        return 1;
    }
    return 0;
}

#include "nitro/types.h"

extern u32 gFieldMinigameWork;

BOOL IsFieldMinigameRoundActive(void)
{
    if (gFieldMinigameWork != 0 && *(s32 *)(gFieldMinigameWork + 0x20) != 0) {
        return 1;
    }
    return 0;
}

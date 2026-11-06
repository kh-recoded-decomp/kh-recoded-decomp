#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerState;
} Session;

extern Session *gFieldSessionWork;

BOOL IsItemScreenSessionState10(void)
{
    BOOL isStateTen = FALSE;

    if (gFieldSessionWork->playerState == 10) {
        isStateTen = TRUE;
    }
    return isStateTen;
}

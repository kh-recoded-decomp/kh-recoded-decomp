#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerStates[4];
} Session;

extern u8 gSelectionRuntimeHeader;
extern Session *gFieldSessionWork;

BOOL AreItemScreenSessionStatesZero(void)
{
    BOOL allIdle = TRUE;
    int index;

    for (index = 0; index < gSelectionRuntimeHeader; index++) {
        if (gFieldSessionWork->playerStates[index] != 0) {
            allIdle = FALSE;
            break;
        }
    }
    return allIdle;
}

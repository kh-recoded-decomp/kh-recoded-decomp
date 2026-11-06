#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerStates[4];
} Session;

extern u8 data_020608c8;
extern Session *gFieldSessionWork;

BOOL AreSlotMenuSessionStatesZero(void)
{
    BOOL allIdle = TRUE;
    int index;

    for (index = 0; index < data_020608c8; index++) {
        if (gFieldSessionWork->playerStates[index] != 0) {
            allIdle = FALSE;
            break;
        }
    }
    return allIdle;
}

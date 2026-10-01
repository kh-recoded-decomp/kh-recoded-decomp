#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerState;
} Session;

extern Session *data_ov001_020a0460;

BOOL func_ov076_020cab1c(void)
{
    BOOL isStateTen = FALSE;

    if (data_ov001_020a0460->playerState == 10) {
        isStateTen = TRUE;
    }
    return isStateTen;
}

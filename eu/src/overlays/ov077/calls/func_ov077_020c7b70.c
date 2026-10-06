#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerState;
} Session;

extern Session *data_ov001_020a0480;

BOOL func_ov077_020c7b70(void)
{
    BOOL isStateTen = FALSE;

    if (data_ov001_020a0480->playerState == 10) {
        isStateTen = TRUE;
    }
    return isStateTen;
}

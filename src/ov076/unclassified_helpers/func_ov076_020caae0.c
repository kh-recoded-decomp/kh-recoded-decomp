#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerStates[4];
} Session;

extern u8 data_020608c8;
extern Session *data_ov001_020a0460;

BOOL func_ov076_020caae0(void)
{
    BOOL allIdle = TRUE;
    int index;

    for (index = 0; index < data_020608c8; index++) {
        if (data_ov001_020a0460->playerStates[index] != 0) {
            allIdle = FALSE;
            break;
        }
    }
    return allIdle;
}

#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27a8];
    int playerStates[4];
} Session;

extern u8 data_020608c8;
extern Session *data_ov001_020a0480;

BOOL func_ov076_020cab00(void)
{
    BOOL allIdle = TRUE;
    int index;

    for (index = 0; index < data_020608c8; index++) {
        if (data_ov001_020a0480->playerStates[index] != 0) {
            allIdle = FALSE;
            break;
        }
    }
    return allIdle;
}

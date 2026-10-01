#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[2232];
    s32 fadeStep;
} MovieScene;

extern MovieScene *data_ov003_020b7d80;

BOOL func_ov022_020a73f4(void)
{
    return data_ov003_020b7d80->fadeStep >= 16;
}

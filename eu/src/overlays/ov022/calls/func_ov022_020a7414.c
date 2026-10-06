#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[2232];
    s32 fadeStep;
} MovieScene;

extern MovieScene *data_ov022_020b7da0;

BOOL func_ov022_020a7414(void)
{
    return data_ov022_020b7da0->fadeStep >= 16;
}

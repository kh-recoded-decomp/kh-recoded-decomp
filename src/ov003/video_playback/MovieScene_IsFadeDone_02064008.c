#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x8c0];
    s32 fadeStep;
} MovieScene;

extern MovieScene *data_ov003_020658c0;

BOOL MovieScene_IsFadeDone_02064008(void)
{
    return data_ov003_020658c0->fadeStep >= 16;
}

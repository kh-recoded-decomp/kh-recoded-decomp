#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x254];
    s8 titleIndex;
} GameState;

extern GameState *data_ov001_020a0480;

int GetContinueTitleIndex(void)
{
    return data_ov001_020a0480->titleIndex;
}

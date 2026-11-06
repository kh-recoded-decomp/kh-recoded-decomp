#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x254];
    s8 titleIndex;
} GameState;

extern GameState *gFieldSessionWork;

int GetContinueTitleIndex(void)
{
    return gFieldSessionWork->titleIndex;
}

#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    s64 startTick;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;

s64 GetCardThreadStartTick_0202726c(void)
{
    return g_cardThreadState_0205fe00.startTick;
}

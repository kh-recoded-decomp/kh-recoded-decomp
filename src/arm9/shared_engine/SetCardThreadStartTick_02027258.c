#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    s64 startTick;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern s64 func_02003fd4(void);

void SetCardThreadStartTick_02027258(void)
{
    g_cardThreadState_0205fe00.startTick = func_02003fd4();
}

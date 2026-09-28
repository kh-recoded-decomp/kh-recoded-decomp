#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
} CommState;

extern CommState *g_commState_020bb760;
extern void func_020365a4(void);

s32 MarkCommChannelBusy_020ba73c(void)
{
    func_020365a4();
    g_commState_020bb760->flags = g_commState_020bb760->flags | 0x8000;
    return 1;
}

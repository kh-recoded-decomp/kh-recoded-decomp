#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
} CommState;

extern CommState *g_commState_020bb760;
extern s32 func_ov001_0206a814(void);
extern s32 func_ov037_020bb4bc(void);

s32 MarkCommBusyWhenReady_020ba944(void)
{
    s32 ready;

    ready = func_ov001_0206a814();
    if (ready != 0) {
        g_commState_020bb760->flags = g_commState_020bb760->flags | 0x8000;
        return 9;
    }
    func_ov037_020bb4bc();
    return -1;
}

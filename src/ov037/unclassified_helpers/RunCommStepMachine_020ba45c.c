#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x18];
    s32 step;
} CommState;

extern CommState *g_commState_020bb760;
extern s32 (*g_commStepTable_020bb6b8[])(void);
extern void func_ov037_020baa70(int flag);
extern void PXI_Init_020baa64(void);

s32 RunCommStepMachine_020ba45c(void)
{
    s32 next;

    do {
        g_commState_020bb760->flags &= 0x7fff;
        next = g_commStepTable_020bb6b8[g_commState_020bb760->step]();
        if (next >= 0) {
            g_commState_020bb760->step = next;
        }
    } while (g_commState_020bb760->flags & 0x8000);
    if (g_commState_020bb760->flags & 8) {
        func_ov037_020baa70(0);
    }
    if (g_commState_020bb760->flags & 4) {
        PXI_Init_020baa64();
    }
    return 0;
}

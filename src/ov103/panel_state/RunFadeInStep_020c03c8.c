#include "nitro/types.h"

typedef struct {
    s32 selection;
    s32 brightness;
    u8 pad_0008[0xCB88 - 8];
    s32 phase;
    s32 step;
    s32 timer;
} Ov103State;

#define REG_MASTER_BRIGHT_MAIN ((vu16 *)0x0400006C)
#define REG_MASTER_BRIGHT_SUB ((vu16 *)0x0400106C)

extern BOOL IsStatePhase3_020bcaa0(void);
extern int func_02006770(vu16 *reg);
extern void func_02006748(vu16 *reg, int value);
extern void SetScenePhase_020c02f4(s32 phase, Ov103State *state);
extern void RefreshRowHighlights_020bf92c(Ov103State *state);
extern void InitSlotPool_020bf668(Ov103State *state);

void RunFadeInStep_020c03c8(Ov103State *state)
{
    if (!IsStatePhase3_020bcaa0()) {
        state->brightness = func_02006770(REG_MASTER_BRIGHT_MAIN);
    } else {
        state->brightness++;
        if (state->brightness >= 0) {
            state->brightness = 0;
        }
        if (state->timer == 0) {
            state->brightness = -16;
        }
        func_02006748(REG_MASTER_BRIGHT_MAIN, state->brightness);
        func_02006748(REG_MASTER_BRIGHT_SUB, state->brightness);
        state->timer++;
    }
    if (state->brightness == 0) {
        SetScenePhase_020c02f4(3, state);
    }
    RefreshRowHighlights_020bf92c(state);
    InitSlotPool_020bf668(state);
}

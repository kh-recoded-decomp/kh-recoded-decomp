#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    u32 mode;
    u8 pad_24[0x34];
    u8 objManager[0x6434];
    u32 slotPrimary;
    u32 slotSecondary;
    u32 slotExtra[2];
} ScreenState;

extern int func_ov001_020725bc(void);
extern int func_ov001_020728c4(void);
extern void func_0204f24c(void *target, u32 index, u32 value);
extern ScreenState *g_screenState_020b6f64;

void ApplyFormationSlots_020b6d90(int formationType)
{
    ScreenState *state;
    int busy;
    int i;

    state = g_screenState_020b6f64;
    busy = func_ov001_020725bc();
    if ((busy == 0) && (busy = func_ov001_020728c4(), busy == 0)) {
        if (formationType == 2) {
            state->mode = 2;
            func_0204f24c(state->objManager, state->slotPrimary, 1);
            func_0204f24c(state->objManager, state->slotSecondary, 3);
            i = 0;
            do {
                func_0204f24c(state->objManager, state->slotExtra[i], 5);
                i = i + 1;
            } while (i < 2);
            return;
        }
        state->mode = 1;
        i = 0;
        func_0204f24c(state->objManager, state->slotPrimary, 0);
        func_0204f24c(state->objManager, state->slotSecondary, 2);
        do {
            func_0204f24c(state->objManager, state->slotExtra[i], 4);
            i = i + 1;
        } while (i < 2);
    }
}

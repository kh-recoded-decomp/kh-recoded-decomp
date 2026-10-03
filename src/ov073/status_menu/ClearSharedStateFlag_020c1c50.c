#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01;
    u8 openCount;
    u8 flags;
    u8 pad_04[0x10];
    BOOL active;
} MenuSharedState;

extern void func_ov073_020c1b28(MenuSharedState *state);
extern void SetStatusElementVisible_020beb5c(int elementId, BOOL visible);
extern void SetScreenBrightness_020bc648(int brightness);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void func_ov039_020bc03c(int value);

void ClearSharedStateFlag_020c1c50(MenuSharedState *state, u8 mask)
{
    BOOL active;

    state->flags &= ~mask;
    active = TRUE;
    if ((state->flags & 1) == 0 && (state->flags != 2 || state->selectedIndex == 0)) {
        active = FALSE;
    }
    state->active = active;
    if (active == FALSE) {
        func_ov073_020c1b28(state);
    }
    state->openCount++;
    if ((state->flags & 2) == 0) {
        SetStatusElementVisible_020beb5c(3, FALSE);
        SetScreenBrightness_020bc648(0);
        SetPrimaryElementEnabled_020bc054(TRUE);
    }
    if ((*(vu16 *)0x04000304 & 0x8000) >> 15 == 0) {
        func_ov039_020bc03c(1);
    }
}

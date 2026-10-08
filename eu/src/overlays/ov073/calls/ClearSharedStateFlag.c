#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01;
    u8 openCount;
    u8 flags;
    u8 pad_04[0x10];
    BOOL active;
} MenuSharedState;

#define SetScreenBrightness HasSceneActiveMenu

extern void ShowStatusPageContents(MenuSharedState *state);
extern void SetStatusElementVisible(int elementId, BOOL visible);
extern void SetScreenBrightness(int brightness);
extern void SetPrimaryElementEnabled(BOOL enabled);
extern void RuntimeState_SetCondition(int value);

void ClearSharedStateFlag(MenuSharedState *state, u8 mask)
{
    BOOL active;

    state->flags &= ~mask;
    active = TRUE;
    if ((state->flags & 1) == 0
        && (state->flags != 2 || state->selectedIndex == 0)) {
        active = FALSE;
    }
    state->active = active;
    if (active == FALSE) {
        ShowStatusPageContents(state);
    }
    state->openCount++;
    if ((state->flags & 2) == 0) {
        SetStatusElementVisible(3, FALSE);
        SetScreenBrightness(0);
        SetPrimaryElementEnabled(TRUE);
    }
    if ((*(vu16 *)0x04000304 & 0x8000) >> 15 == 0) {
        RuntimeState_SetCondition(1);
    }
}

#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[0xb44 - 1];
    u8 list[4];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);
extern int GetPlayerLevelTier_020c1418(void);
extern void ScrollListWidgetTo_020c3ee0(void *list, int value);

void SyncSharedListScroll_020c2ac8(void)
{
    MenuSharedState *state = func_ov039_020bc630();
    void *list = state->list;

    if (state->selectedIndex == 4) {
        ScrollListWidgetTo_020c3ee0(list, GetPlayerLevelTier_020c1418());
    }
}

#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[0xb44 - 1];
    u8 list[4];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);
extern void SetListWidgetMode_020c3f34(void *list, u8 mode);

void SetSharedListMode_020c2aec(int mode)
{
    MenuSharedState *state = func_ov039_020bc630();
    void *list = state->list;

    if (state->selectedIndex == 4) {
        SetListWidgetMode_020c3f34(list, mode);
    }
}

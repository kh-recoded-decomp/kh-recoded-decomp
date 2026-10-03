#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[0xb44 - 1];
    u8 list[4];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);
extern void SetListWidgetEntries_020c3ffc(void *list, const u16 *ids);

void SetSharedListEntries_020c2c24(const u16 *ids)
{
    MenuSharedState *state = func_ov039_020bc630();
    void *list = state->list;

    if (state->selectedIndex == 4) {
        SetListWidgetEntries_020c3ffc(list, ids);
    }
}

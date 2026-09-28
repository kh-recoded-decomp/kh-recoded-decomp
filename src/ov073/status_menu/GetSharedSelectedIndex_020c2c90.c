#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);

int GetSharedSelectedIndex_020c2c90(void)
{
    MenuSharedState *state = func_ov039_020bc630();

    if (state != NULL) {
        return state->selectedIndex;
    }
    return 0;
}

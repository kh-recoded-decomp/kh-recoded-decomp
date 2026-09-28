#include "nitro/types.h"

typedef struct MenuSharedState MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);
extern void func_ov073_020c1be0(MenuSharedState *state, u8 mask);
extern void func_ov073_020c1c50(MenuSharedState *state, u8 mask);

void ToggleSharedStateFlag_020c1d1c(BOOL enable)
{
    MenuSharedState *state = func_ov039_020bc630();

    if (enable) {
        func_ov073_020c1be0(state, 1);
    } else {
        func_ov073_020c1c50(state, 1);
    }
}

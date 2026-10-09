#include "nitro/types.h"
#include "src/ov002/panel_state/MenuTouchState.h"

void GetMenuTouchDisplacement_02066a90(MenuTouchPosition *out)
{
    MenuTouchPosition displacement;
    MenuTouchState *state = gMenuCursorState;
    displacement.x = state->x - state->startX;
    displacement.y = state->y - state->startY;
    *out = displacement;
}

#include "nitro/types.h"
#include "ov002/MenuTouchState.h"

void GetMenuTouchDisplacement_02066a90(MenuTouchPosition *out)
{
    MenuTouchPosition displacement;
    MenuTouchState *state = gMenuCursorState;
    displacement.x = state->x - state->startX;
    displacement.y = state->y - state->startY;
    *out = displacement;
}

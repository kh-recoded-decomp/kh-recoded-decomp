#include "../include/ov002/MenuTouchState.h"

void GetMenuCursorDelta(MenuTouchPosition *out)
{
    MenuTouchState *state = gMenuCursorState;
    int current = state->current;
    int previous = gMenuCursorNextPoint[current];
    MenuTouchPosition delta;

    delta.x = state->points[current].x;
    delta.y = state->points[current].y;
    delta.x -= state->points[previous].x;
    delta.y -= state->points[previous].y;
    *out = delta;
}

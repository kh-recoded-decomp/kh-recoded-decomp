#include "nitro/types.h"
#include "src/ov002/panel_state/MenuTouchState.h"
extern void func_01ff8830(void *dst, int value, u32 size);

void GetMenuCursorPosition_02066bdc(MenuTouchPosition *out)
{
    MenuTouchPosition position;

    func_01ff8830(&position, 0, sizeof(position));
    if (gMenuCursorState != NULL) {
        position.x = gMenuCursorState->points[gMenuCursorState->current].x;
        position.y = gMenuCursorState->points[gMenuCursorState->current].y;
    }
    *out = position;
}

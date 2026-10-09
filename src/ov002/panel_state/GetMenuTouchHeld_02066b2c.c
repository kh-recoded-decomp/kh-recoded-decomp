#include "nitro/types.h"
#include "ov002/MenuTouchState.h"

u32 GetMenuTouchHeld_02066b2c(u32 *out)
{
    if (gMenuCursorState == NULL) {
        return 0;
    }
    if (out != NULL) {
        s16 current = gMenuCursorState->current;
        out[0] = gMenuCursorState->points[current].x;
        out[1] = gMenuCursorState->points[current].y;
    }
    return gMenuCursorState->touching;
}

#include "nitro/types.h"
#include "ov002/MenuTouchState.h"

u32 GetMenuTouchPressed_02066b84(u32 *out)
{
    if (gMenuCursorState == NULL) {
        return 0;
    }
    if (out != NULL) {
        s16 current = gMenuCursorState->current;
        out[0] = gMenuCursorState->points[current].x;
        out[1] = gMenuCursorState->points[current].y;
    }
    return gMenuCursorState->pressed;
}

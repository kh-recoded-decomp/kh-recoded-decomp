#include "nitro/types.h"
#include "src/ov002/panel_state/MenuTouchState.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern int CopyRecentTouchPoints_0202b618(TouchSample *table);
extern void GetMenuTouchDisplacement_02066a90(MenuTouchPosition *out);

u32 UpdateMenuTouch_0206671c(void)
{
    TouchSample samples[4];
    MenuTouchPosition pressPos;
    MenuTouchPosition releasePos;
    MenuTouchPosition delta;
    MenuTouchPosition dragPos;
    MenuTouchPosition rectSize;
    u8 touching;
    int count;
    int i;
    int x;
    int y;
    u32 events;

    touching = FALSE;
    events = 0;
    count = CopyRecentTouchPoints_0202b618(samples);
    if (count != 0) {
        for (i = 0; i < count; i++) {
            x = samples[i].x;
            y = samples[i].y;
            if (x >= 256) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            if (y >= 192) {
                y = 191;
            } else if (y < 0) {
                y = 0;
            }
            gMenuCursorState->prevX = gMenuCursorState->x;
            gMenuCursorState->prevY = gMenuCursorState->y;
            gMenuCursorState->x = x;
            gMenuCursorState->y = y;
        }
        touching = TRUE;
    }
    gMenuCursorState->wasTouching = gMenuCursorState->touching;
    gMenuCursorState->touching = touching;
    gMenuCursorState->pressed = (u8)(gMenuCursorState->wasTouching ^ gMenuCursorState->touching) & gMenuCursorState->touching;
    gMenuCursorState->released = ~gMenuCursorState->touching & gMenuCursorState->wasTouching;
    if (gMenuCursorState->pressed) {
        events |= 1;
        gMenuCursorState->prevX = gMenuCursorState->x;
        gMenuCursorState->prevY = gMenuCursorState->y;
        pressPos.x = gMenuCursorState->x;
        pressPos.y = gMenuCursorState->y;
        gMenuCursorState->startX = gMenuCursorState->x;
        gMenuCursorState->startY = gMenuCursorState->y;
        gMenuCursorState->dragged = FALSE;
        for (i = 0; i < 3; i++) {
            gMenuCursorState->points[i].x = pressPos.x;
            gMenuCursorState->points[i].y = pressPos.y;
        }
        if (gMenuCursorState->callback != NULL) {
            gMenuCursorState->callback(1, &pressPos, 0);
        }
    }
    if (gMenuCursorState->released) {
        events |= 2;
        releasePos.x = gMenuCursorState->x;
        releasePos.y = gMenuCursorState->y;
        if (gMenuCursorState->callback != NULL) {
            gMenuCursorState->callback(2, &releasePos, 0);
        }
        if (!gMenuCursorState->dragged) {
            events |= 4;
            if (gMenuCursorState->callback != NULL) {
                gMenuCursorState->callback(4, &releasePos, 0);
            }
        }
    }
    if (gMenuCursorState->touching) {
        GetMenuTouchDisplacement_02066a90(&rectSize);
        delta = rectSize;
        if (delta.x < -4 || delta.x > 4 || delta.y < -4 || delta.y > 4) {
            events |= 8;
            gMenuCursorState->dragged = TRUE;
            dragPos.x = gMenuCursorState->x;
            dragPos.y = gMenuCursorState->y;
            gMenuCursorState->points[gMenuCursorState->current].x = dragPos.x;
            gMenuCursorState->points[gMenuCursorState->current].y = dragPos.y;
            gMenuCursorState->current = gMenuCursorNextPoint[gMenuCursorState->current];
            if (gMenuCursorState->callback != NULL) {
                gMenuCursorState->callback(8, &dragPos, 0);
            }
        }
    }
    return events;
}

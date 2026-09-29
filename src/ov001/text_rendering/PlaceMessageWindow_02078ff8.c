#include "nitro/types.h"

typedef struct {
    s32 layout;
} MessageContext;

typedef struct {
    s32 anchor;
    u8 pad_04[0xc];
    u16 tileX;
    u16 tileY;
    u8 pad_14[0x34];
    s32 focusX;
    s32 focusY;
} MessageWindow;

typedef struct {
    s32 width;
    s32 height;
} TextSize;

typedef struct {
    s16 x;
    s16 y;
    s16 pad_04[2];
    s16 hasTail;
} WindowRect;

extern MessageContext *g_activeContext_020a04c4;
extern int func_ov001_02078fb4(MessageWindow *window);

int PlaceMessageWindow_02078ff8(MessageWindow *window, TextSize *size, WindowRect *rect, int extraWidth)
{
    int result = 0;
    int pos;
    int limit;

    switch (g_activeContext_020a04c4->layout) {
    case 2:
        if (extraWidth > 0) {
            window->tileX = 1;
        } else {
            window->tileX = 16 - (size->width + 2) / 2;
        }
        rect->x = window->tileX + 1;
        if (window->anchor == 0) {
            rect->y = 2;
        } else {
            rect->y = 22 - size->height;
        }
        rect->hasTail = 1;
        break;
    case 1:
        switch (window->anchor) {
        case 0:
            window->tileX = 16 - (extraWidth + size->width + 2) / 2;
            rect->x = window->tileX + 1;
            rect->y = 3;
            break;
        case 2: {
            int height;

            window->tileX = 16 - (extraWidth + size->width + 2) / 2;
            height = size->height;
            rect->x = window->tileX + 1;
            rect->y = 11 - height / 2;
            break;
        }
        case 3:
            window->tileX = 0;
            rect->x = window->tileX + 1;
            rect->y = 5;
            break;
        case 4:
            window->tileX = 32 - size->width;
            rect->x = window->tileX - 1;
            rect->y = 5;
            break;
        }
        result = 1;
        break;
    case 3:
    case 4:
        window->tileX = 16 - (size->width + 3) / 2;
        window->tileY = 12 - (size->height + 3) / 2;
        rect->x = window->tileX + 1;
        rect->y = window->tileY + 1;
        break;
    case 5:
    case 7:
    case 10:
        window->tileX = 16 - (size->width + 3) / 2;
        window->tileY = 8 - (size->height + 3) / 2;
        rect->x = window->tileX + 1;
        rect->y = window->tileY + 1;
        break;
    case 6:
        window->tileX = 16 - (size->width + 3) / 2;
        window->tileY = 8 - (size->height + 3) / 2;
        rect->x = window->tileX + 1;
        rect->y = window->tileY + 1;
        break;
    case 8:
        window->tileX = 16 - (size->width + 3) / 2;
        rect->x = window->tileX + 1;
        if (window->anchor == 0) {
            rect->y = 2;
        } else {
            rect->y = 22 - size->height;
        }
        rect->hasTail = 1;
        break;
    case 9:
        pos = (window->focusX + 4) / 8 - (size->width + 3) / 2;
        limit = 31 - (size->width + 2);
        window->tileX = pos > limit ? limit : (pos < 0 ? 0 : pos);
        pos += func_ov001_02078fb4(window);
        limit = 31 - (size->width + 2);
        window->tileX = pos > limit ? limit : (pos < 0 ? 0 : pos);
        rect->x = window->tileX + 1;
        pos = (window->focusY + 4) / 8 - (size->height + 2);
        limit = 22 - (size->height + 2);
        window->tileY = pos > limit ? limit : (pos < 1 ? 1 : pos);
        rect->y = window->tileY + 1;
        rect->hasTail = 1;
        break;
    }
    return result;
}

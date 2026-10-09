#ifndef KH_RECODED_MENU_TOUCH_STATE_H
#define KH_RECODED_MENU_TOUCH_STATE_H

#include "nitro/types.h"

typedef struct MenuTouchPosition {
    int x;
    int y;
} MenuTouchPosition;

typedef struct MenuTouchPoint {
    u16 x;
    u16 y;
    u8 pad_04[4];
} MenuTouchPoint;

typedef void (*MenuTouchCallback)(int event, MenuTouchPosition *position, int arg);

typedef struct MenuTouchState {
    MenuTouchCallback callback;
    u8 wasTouching : 1;
    u8 touching : 1;
    u8 pressed : 1;
    u8 released : 1;
    u8 dragged : 1;
    u8 pad_04_b5 : 3;
    u8 pad_05;
    MenuTouchPoint points[3];
    s16 current;
    s16 startX;
    s16 startY;
    s16 x;
    s16 y;
    s16 prevX;
    s16 prevY;
} MenuTouchState;

extern MenuTouchState *gMenuCursorState;
extern s8 gMenuCursorNextPoint[4];

#endif

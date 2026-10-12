#include "nitro/types.h"

typedef struct SlotMenuCursorRect {
    s32 x;
    s32 y;
    BOOL enabled;
    s32 frame;
    s32 tag;
    s32 group;
} SlotMenuCursorRect;

typedef struct SlotMenuCursorState {
    s32 state;
    u8 reserved004[0x14 - 4];
    s32 column;
    u8 reserved018[0x28 - 0x18];
    s32 alternateLayout;
    u8 reserved02c[0x7fc0 - 0x2c];
    u8 messageWindow[0x11ee0 - 0x7fc0];
    s32 inputMode;
    u8 reserved11ee4[2];
    s16 slotIndex;
    u8 reserved11ee8[0x1c694 - 0x11ee8];
    SlotMenuCursorRect cursors[4];
    u8 reserved1c6f4[0x4a068 - 0x1c6f4];
    s32 cursorLocked;
} SlotMenuCursorState;

extern BOOL MessageWindow_IsFinished(void *window);
extern BOOL GetPrimaryElementEnabled(void);

#pragma opt_propagation off
static inline BOOL IsPrimaryElementDisabled(void)
{
    return !GetPrimaryElementEnabled();
}
#pragma opt_propagation on

void SlotMenu_UpdateCursorLayout(SlotMenuCursorState *menu, BOOL forceThirdMarker)
{
    s32 x;
    s32 y;
    int i;

    menu->cursors[0].enabled = menu->cursorLocked == 0 && menu->state < 2;
    menu->cursors[1].enabled = 0;
    menu->cursors[2].enabled = 0;
    menu->cursors[3].enabled = 0;
    if ((menu->state == 3 || menu->state == 8) && MessageWindow_IsFinished(menu->messageWindow)) {
        return;
    }
    y = (menu->column << 4) + 16 + (menu->slotIndex << 6);
    if (forceThirdMarker) {
        menu->cursors[2].enabled = 1;
        x = 48;
    } else {
        if (menu->column == 2) {
            x = 64;
            menu->cursors[3].enabled = 1;
        } else {
            x = 48;
            menu->cursors[1].enabled = 1;
        }
        if (menu->alternateLayout != 0) {
            x = 48;
        }
    }
    for (i = 0; i < 4; ++i) {
        SlotMenuCursorRect *cursor = &menu->cursors[i];
        cursor->x = x;
        cursor->y = y;
    }
    if (!GetPrimaryElementEnabled() || menu->state == 9 ||
        IsPrimaryElementDisabled() || menu->inputMode == 1) {
        menu->cursors[0].enabled = 0;
    }
}

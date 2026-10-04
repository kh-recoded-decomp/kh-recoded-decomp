#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 pad_08[8];
} TextFrame;

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
    s32 x;
    s32 y;
    s32 param;
    u8 textLayer[0x34];
    u16 *text;
    TextFrame frame;
} PopupWindow;

typedef struct {
    u8 pad_00[0x10];
    int frameSlot;
} PopupManager;

extern PopupManager *g_popupManager_020c373c;
extern void DrawPopupText_020c19d0(PopupWindow *window);
extern int func_020019f4(void *layer);
extern void SetPopupSlotPos_020c1c58(int slotIndex, int x, int y, int offsetX, int offsetY);
extern void SetPopupSlotVisible_020c1d48(int slotIndex, BOOL visible);
extern void SetPopupState_020c2784(PopupWindow *window, s32 state);

void ShowPopupFrame_020c1fe4(PopupWindow *window)
{
    int lineHeight;

    DrawPopupText_020c19d0(window);
    lineHeight = func_020019f4(window->textLayer);
    SetPopupSlotPos_020c1c58(g_popupManager_020c373c->frameSlot, (window->frame.x + window->frame.width) * 8,
                             (window->frame.y + window->frame.height) * 8 + lineHeight / 2 - 4, window->x, window->y);
    SetPopupSlotVisible_020c1d48(g_popupManager_020c373c->frameSlot, TRUE);
    SetPopupState_020c2784(window, 5);
}

#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

typedef struct MenuCallback {
    void (*handler)(SlotMenu *menu);
    SlotMenu *context;
} MenuCallback;

typedef union PanelSize {
    u32 packed;
    struct {
        u16 width;
        u16 height;
    } dim;
} PanelSize;

struct SlotMenu {
    u8 pad_00000[0x4e80];
    int messageTable[3];
    u8 pad_04E8C[0x7fc0 - 0x4e8c];
    u8 panel[0x11bf8 - 0x7fc0];
    u32 panelFlags;
    u8 pad_11BFC[0x11c0c - 0x11bfc];
    MenuCallback onCancel;
    MenuCallback onConfirm;
    u16 buttonStates[4];
};

extern void *func_ov027_020ba2a8(int *table, int index);
extern PanelSize func_ov076_020cb2b8(void *panel, int owner, void *message);
extern void MenuPanel_InitStandard_020cb380(void *panel, int owner, int x, int y, u16 width, u16 height, void *message);
extern void func_ov076_020c8178(SlotMenu *menu, int mode);
extern void func_ov076_020c8a70(SlotMenu *menu);
extern void func_ov076_020cb9a0(SlotMenu *menu);

void SlotMenu_OpenMessagePanel_020c6308(SlotMenu *menu, int owner, int x, u16 y, int messageId)
{
    void *message = func_ov027_020ba2a8(menu->messageTable, messageId);
    PanelSize size = func_ov076_020cb2b8(menu->panel, owner, message);
    MenuCallback callback;

    menu->buttonStates[0] = 1;
    menu->buttonStates[1] = 1;
    menu->buttonStates[2] = 1;
    menu->buttonStates[3] = 3;
    callback.handler = func_ov076_020c8a70;
    callback.context = menu;
    menu->onConfirm = callback;
    if (messageId == 0x5d) {
        MenuCallback cancel;
        cancel.handler = func_ov076_020cb9a0;
        cancel.context = menu;
        menu->onCancel = cancel;
        menu->panelFlags |= 8;
    }
    MenuPanel_InitStandard_020cb380(menu->panel, owner, x, y, size.dim.width, size.dim.height, message);
    func_ov076_020c8178(menu, 0);
}

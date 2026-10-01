#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

typedef struct MenuCallback {
    void (*handler)(SlotMenu *menu);
    SlotMenu *context;
} MenuCallback;

struct SlotMenu {
    u8 pad_00000[0x11c04];
    MenuCallback onReturn;
};

extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);

void SlotMenu_SetReturnCallback_020c89c4(SlotMenu *menu)
{
    MenuCallback callback;
    callback.handler = SlotMenu_ResetToBrowse_020c4ea8;
    callback.context = menu;
    menu->onReturn = callback;
}

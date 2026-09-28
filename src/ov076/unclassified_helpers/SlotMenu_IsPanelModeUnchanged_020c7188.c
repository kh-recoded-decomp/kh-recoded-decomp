#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x24];
    u8 panel[0x11ebc];
    s32 panelMode;
} SlotMenu;

extern BOOL func_ov039_020bc0d4(void);
extern int MenuPanel_Update_020cc33c(void *panel);

BOOL SlotMenu_IsPanelModeUnchanged_020c7188(SlotMenu *menu)
{
    int mode;

    if (!func_ov039_020bc0d4()) {
        return TRUE;
    }
    mode = MenuPanel_Update_020cc33c(menu->panel);
    if (menu->panelMode == mode) {
        return TRUE;
    }
    menu->panelMode = mode;
    return FALSE;
}

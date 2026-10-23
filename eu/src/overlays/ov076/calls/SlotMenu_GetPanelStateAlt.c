#include "nitro/types.h"

typedef struct MenuPanel {
    u8 pad_00[4];
    s32 state;
} MenuPanel;

typedef struct SlotMenu {
    u8 pad_0000[0x24];
    MenuPanel panel;
} SlotMenu;

BOOL SlotMenu_GetPanelStateAlt(SlotMenu *menu)
{
    BOOL state = menu->panel.state;

    if (state) {
        state = menu->panel.state;
    }
    return state;
}

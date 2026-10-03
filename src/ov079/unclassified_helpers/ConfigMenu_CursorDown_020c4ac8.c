#include "nitro/types.h"

typedef struct ConfigOption {
    u8 count;
    u8 value;
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[7];
    ConfigOption *options[6];
} ConfigPage;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 pad_02;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[0x4b];
    ConfigPage pages[3];
} ConfigMenu;

extern void PlaySoundEffect_0204d924(int bank, int id);

void ConfigMenu_CursorDown_020c4ac8(ConfigMenu *menu)
{
    menu->row++;
    if (menu->row == menu->pages[menu->page].rowCount) {
        menu->row = 0;
    }
    menu->dirty = TRUE;
    PlaySoundEffect_0204d924(0, 0);
}

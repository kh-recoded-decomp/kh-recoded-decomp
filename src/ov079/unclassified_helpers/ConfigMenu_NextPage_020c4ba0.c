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

extern void CallStateWidget_020bc14c(int a, int b, int c, int d, int e);
extern void PlaySoundEffect_0204d924(int bank, int id);

void ConfigMenu_NextPage_020c4ba0(ConfigMenu *menu)
{
    int lastRow;

    menu->page++;
    if (menu->page == 3) {
        menu->page = 0;
    }
    lastRow = menu->pages[menu->page].rowCount - 1;
    if (menu->row > lastRow) {
        menu->row = lastRow;
    }
    CallStateWidget_020bc14c(10, 0, 0, 0x20, 0x18);
    menu->dirty = TRUE;
    menu->pageChanged = TRUE;
    PlaySoundEffect_0204d924(0, 2);
}

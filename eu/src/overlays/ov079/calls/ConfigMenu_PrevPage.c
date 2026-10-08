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

extern void CallStateWidget(int a, int b, int c, int d, int e);
extern void PlaySoundEffect(int bank, int id);

void ConfigMenu_PrevPage(ConfigMenu *menu)
{
    int lastRow;

    if (menu->page == 0) {
        menu->page = 3;
    }
    menu->page--;
    lastRow = menu->pages[menu->page].rowCount - 1;
    if (menu->row > lastRow) {
        menu->row = lastRow;
    }
    CallStateWidget(10, 0, 0, 0x20, 0x18);
    menu->dirty = TRUE;
    menu->pageChanged = TRUE;
    PlaySoundEffect(0, 2);
}

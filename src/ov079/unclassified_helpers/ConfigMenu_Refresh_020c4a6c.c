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

extern void func_ov079_020c487c(ConfigMenu *menu);
extern void func_ov079_020c4928(ConfigMenu *menu);

void ConfigMenu_Refresh_020c4a6c(ConfigMenu *menu)
{
    if (menu->dirty || menu->pageChanged) {
        func_ov079_020c487c(menu);
        func_ov079_020c4928(menu);
        if (menu->dirty) {
            menu->dirty--;
        }
        if (menu->pageChanged) {
            menu->pageChanged--;
        }
    }
}

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

void ConfigMenu_PrevValue_020c4af4(ConfigMenu *menu)
{
    ConfigOption *option = menu->pages[menu->page].options[menu->row];

    if (option->value == 0) {
        option->value = option->count;
    }
    option->value--;
    menu->dirty = TRUE;
    PlaySoundEffect_0204d924(0, 0);
}

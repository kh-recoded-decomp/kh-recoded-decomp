#include "nitro/types.h"

typedef struct TabMenu {
    u8 mode;
    u8 dirty;
    u8 pad2;
    s8 tab;
    u8 pad4[8];
    int hasExtraTab;
} TabMenu;

extern s8 data_ov085_020c22c4[];
extern void PlaySoundEffect_0204d924(int channel, int id);
extern BOOL func_ov085_020c14c0(TabMenu *menu, int category);
extern void func_ov085_020c1164(TabMenu *menu, int tab);
extern void func_ov085_020c1550(TabMenu *menu);

void SelectNextTab_020c1894(TabMenu *menu)
{
    int hidden = 1;
    s16 count;
    s16 tab;

    if (menu->hasExtraTab != 0) {
        hidden = 0;
    }
    count = 5 - hidden;
    if (menu->mode == 0) {
        tab = menu->tab;
        do {
            tab++;
            if (tab == count) {
                tab = 0;
            }
        } while (menu->tab != tab && !func_ov085_020c14c0(menu, data_ov085_020c22c4[tab]));
        if (menu->tab != tab) {
            PlaySoundEffect_0204d924(0, 2);
        }
        menu->tab = tab;
        func_ov085_020c1164(menu, menu->tab);
        func_ov085_020c1550(menu);
        menu->dirty = 1;
    }
}

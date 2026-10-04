#include "nitro/types.h"

typedef struct SelectMenu {
    u8 selection;
    u8 enabledMask;
    u8 dirty;
} SelectMenu;

extern void func_ov084_020bf9e8(SelectMenu *menu);
extern void func_ov084_020bfa44(SelectMenu *menu);
extern void func_ov084_020bfadc(SelectMenu *menu);

void UpdateSelectMenu_020bfb64(SelectMenu *menu)
{
    if (menu->dirty != 0) {
        func_ov084_020bf9e8(menu);
        func_ov084_020bfa44(menu);
        menu->dirty--;
    }
    func_ov084_020bfadc(menu);
}

#include "nitro/types.h"

typedef struct {
    u8 pad00;
    u8 confirmed;
    s8 selection;
    s8 cursor;
    u8 pad04[4];
    s32 state;
    u8 pad0c[0x16];
    u8 dirty : 1;
    u8 pad23[0x69c5];
    u8 menu[1];
} SaveMenu;

#define REG_SUB_DISPCNT (*(vu32 *)0x04001000)

extern SaveMenu *data_ov002_0206c464;

extern BOOL IsButtonBPressed_020632c8(void);
extern void PlaySoundEffect_0204d924(int bank, int id);
extern void ChangeMenuState(int result);
extern u16 *func_ov002_02062000(void);
extern void func_ov002_020643a0(void);
extern void func_ov002_02064c9c(int flag);
extern void func_ov027_020b8ca8(void *menu, u16 entry);
extern int func_ov027_020b90a4(void *menu, int index);
extern void func_ov027_020b96e4(void *menu, int handle);
extern void func_ov027_020b9620(void *menu, int handle);
extern void SetEntrySlotsVisible_020b9580(void *menu, int handle, int visible);

void UpdateQuitMenuState(void)
{
    u8 *menu;

    switch (data_ov002_0206c464->state) {
    case 0:
        if (IsButtonBPressed_020632c8()) {
            REG_SUB_DISPCNT = (REG_SUB_DISPCNT & ~0x1f00) | 0x1e00;
            func_ov002_020643a0();
            menu = data_ov002_0206c464->menu;
            SetEntrySlotsVisible_020b9580(menu, func_ov027_020b90a4(menu, 0xb), 0);
            menu = data_ov002_0206c464->menu;
            SetEntrySlotsVisible_020b9580(menu, func_ov027_020b90a4(menu, 0xc), 0);
            func_ov002_02064c9c(1);
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            func_ov027_020b9620(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            PlaySoundEffect_0204d924(2, 2);
            ChangeMenuState(1);
            return;
        }
        switch (data_ov002_0206c464->selection) {
        case 0:
            func_ov027_020b8ca8(data_ov002_0206c464->menu, *func_ov002_02062000());
            break;
        case 1:
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xc));
            data_ov002_0206c464->state = 5;
            break;
        case 2:
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xb));
            data_ov002_0206c464->state = 5;
            break;
        }
        break;
    case 5:
        data_ov002_0206c464->state = 10;
        break;
    case 10:
        switch (data_ov002_0206c464->selection) {
        case 1:
            SetEntrySlotsVisible_020b9580(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xb), 0);
            SetEntrySlotsVisible_020b9580(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xc), 0);
            REG_SUB_DISPCNT = (REG_SUB_DISPCNT & ~0x1f00) | 0x1e00;
            func_ov002_020643a0();
            func_ov002_02064c9c(1);
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            func_ov027_020b9620(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, data_ov002_0206c464->cursor + 1));
            PlaySoundEffect_0204d924(2, 1);
            ChangeMenuState(1);
            break;
        case 2:
            data_ov002_0206c464->dirty = TRUE;
            data_ov002_0206c464->confirmed = 1;
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xb));
            ChangeMenuState(4);
            PlaySoundEffect_0204d924(2, 1);
            break;
        }
        break;
    }
}

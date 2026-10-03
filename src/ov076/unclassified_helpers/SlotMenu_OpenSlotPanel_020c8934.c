#include "nitro/types.h"

typedef struct ScreenPos {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u8 pad_08[4];
} ScreenPos;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x10];
    s32 column;
    u8 pad_00018[0xc];
    u8 panel[0x11ee6 - 0x24];
    s16 slotIndex;
} SlotMenu;

extern ScreenPos data_ov076_020cd2cc;
extern ScreenPos data_ov076_020cd2d8;

extern void func_ov076_020c52f8(SlotMenu *menu, u16 slot, u16 column, int mode, ScreenPos *pos);
extern BOOL func_ov076_020cbba0(void *panel, SlotMenu *owner, int (*getValue)(int *), void (*onClose)(SlotMenu *), ScreenPos *pos, int style);
extern int Obj_GetWordC_020c5244(int *p);
extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);
extern void *func_ov039_020bc1bc(void);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);

void SlotMenu_OpenSlotPanel_020c8934(SlotMenu *menu)
{
    func_ov076_020c52f8(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2cc);
    func_ov076_020c52f8(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2d8);
    if (func_ov076_020cbba0(menu->panel, menu, Obj_GetWordC_020c5244, SlotMenu_ResetToBrowse_020c4ea8, &data_ov076_020cd2cc, 2)) {
        menu->state = 2;
        SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
    }
}

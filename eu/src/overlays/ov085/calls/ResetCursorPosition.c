#include "nitro/types.h"

typedef struct CursorPos {
    s16 x;
    s16 y;
    s16 z;
} CursorPos;

typedef struct CursorMenu {
    u8 pad_0000[2];
    u8 usePageIndex;
    u8 pad_0003[0x19];
    CursorPos position;
    u8 pad_0022[0x1ae];
    void *layout;
    u8 pad_01d4[0x4630];
    u16 pageIndex;
    u8 pad_4806[0x164a];
    u32 itemIndex;
} CursorMenu;

extern void func_ov034_020bdf30(CursorPos *position, void *layout, int animate);

void ResetCursorPosition(CursorMenu *menu)
{
    if (menu->usePageIndex) {
        menu->position.x = menu->pageIndex;
    } else {
        menu->position.x = menu->itemIndex;
    }
    menu->position.y = 0;
    menu->position.z = 0;
    func_ov034_020bdf30(&menu->position, menu->layout, 1);
}

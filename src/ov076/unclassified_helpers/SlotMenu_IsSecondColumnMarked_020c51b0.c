#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00[0x14];
    s32 column;
} SlotMenu;

extern int SlotMenu_GetCursorMarkType_020c7208(SlotMenu *menu);

BOOL SlotMenu_IsSecondColumnMarked_020c51b0(SlotMenu *menu)
{
    int markType = SlotMenu_GetCursorMarkType_020c7208(menu);

    if ((markType == 0 || markType == 1) && menu->column == 1) {
        return TRUE;
    }
    return FALSE;
}

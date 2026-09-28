#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00[0x14];
    s32 column;
} SlotMenu;

extern int SlotMenu_GetCursorMarkType_020c7208(SlotMenu *menu);

BOOL SlotMenu_IsThirdColumnMarked_020c5190(SlotMenu *menu)
{
    int markType = SlotMenu_GetCursorMarkType_020c7208(menu);

    if ((markType == 0 || markType == 2) && menu->column == 2) {
        return TRUE;
    }
    return FALSE;
}

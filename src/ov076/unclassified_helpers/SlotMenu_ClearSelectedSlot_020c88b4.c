#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
} SlotMenu;

extern void SlotMenu_UnequipSlotEntry_020c89e0(SlotMenu *menu, int slot, int column);
extern void SlotMenu_ReloadSlot_020c6f60(SlotMenu *menu, int slot, int mode);
extern void SlotMenu_LockTouchUntilCommit_020c88dc(SlotMenu *menu, BOOL unused);

void SlotMenu_ClearSelectedSlot_020c88b4(SlotMenu *menu)
{
    int slot = menu->slotIndex;

    SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, menu->column);
    SlotMenu_ReloadSlot_020c6f60(menu, slot, 0);
    SlotMenu_LockTouchUntilCommit_020c88dc(menu, TRUE);
}

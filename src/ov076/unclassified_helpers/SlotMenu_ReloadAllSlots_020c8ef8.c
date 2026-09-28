#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11ee4];
    s16 slotCount;
} SlotMenu;

extern SlotMenu *g_slotMenu_020cd3e0;
extern void SlotMenu_ReloadSlot_020c6f60(SlotMenu *menu, int slot, int mode);

void SlotMenu_ReloadAllSlots_020c8ef8(void)
{
    int slot = 0;
    s16 slotCount = g_slotMenu_020cd3e0->slotCount;

    for (; slot < slotCount; slot++) {
        SlotMenu_ReloadSlot_020c6f60(g_slotMenu_020cd3e0, slot, 0);
    }
}

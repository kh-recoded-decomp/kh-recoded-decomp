#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11ee6];
    s16 slotIndex;
    s16 cursorSlot;
} SlotMenu;

extern void *func_ov039_020bc1bc(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SetWidgetRootTouchEnabled_020b984c(void *root, BOOL enabled);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void SlotMenu_OpenMessage_020c6308(SlotMenu *menu, int windowType, int arg2, u16 style, int messageId);

void SlotMenu_OpenSlotMessage_020c8388(SlotMenu *menu, int messageId)
{
    void *root = func_ov039_020bc1bc();
    BOOL moved;
    int style;

    if (menu->slotIndex != menu->cursorSlot) {
        moved = TRUE;
    } else {
        moved = FALSE;
    }

    PlaySoundEffect_0204d924(1, 1);
    SetWidgetRootTouchEnabled_020b984c(root, TRUE);
    func_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x600);
    style = 3;
    if (!moved) {
        style = 0xb;
    }
    SlotMenu_OpenMessage_020c6308(menu, 2, 0, style, messageId);
}

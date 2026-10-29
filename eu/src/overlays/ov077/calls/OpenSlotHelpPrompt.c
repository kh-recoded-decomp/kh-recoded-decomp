#include "src/overlays/ov077/SlotHelpPrompt.h"

typedef struct ItemMenuWork {
    u8 unknown00[0x14];
    u8 promptScreen[0x11ff4 - 0x14];
    s32 mode;
    s32 slot;
} ItemMenuWork;

SlotHelpPromptDefinition gEquipmentOtherSlotHelpPrompt = {
    0x4a, 0x51, 2, 1, 0x40, 0x58, 0
};

typedef char ItemMenuModeOffset[(u32)&((ItemMenuWork *)0)->mode == 0x11ff4 ? 1 : -1];
typedef char ItemMenuSlotOffset[(u32)&((ItemMenuWork *)0)->slot == 0x11ff8 ? 1 : -1];

extern BOOL OpenItemPrompt(void *, void *, BOOL (*)(void *), void *,
                             const SlotHelpPromptDefinition *, void *);
extern void SetModeTwoAndRefresh(ItemMenuWork *);
extern void *func_ov039_020bc1dc(void);
extern void SetFlagGatedElementsVisible(void *, BOOL);

BOOL OpenSlotHelpPrompt(ItemMenuWork *work)
{
    BOOL opened;

    switch (work->slot) {
    case 0:
        opened = OpenItemPrompt(work->promptScreen, work, NULL,
            (void *)SetModeTwoAndRefresh, &gEquipmentSlot0HelpPrompt, (void *)1);
        break;
    case 1:
        opened = OpenItemPrompt(work->promptScreen, work, NULL,
            (void *)SetModeTwoAndRefresh, &gEquipmentSlot1HelpPrompt, (void *)1);
        break;
    default:
        if (work->slot > 2) {
            gEquipmentOtherSlotHelpPrompt.align = -1;
            gEquipmentOtherSlotHelpPrompt.unknown06 += (u16)((u32)(work->slot - 2) << 4);
        }
        opened = OpenItemPrompt(work->promptScreen, work, NULL,
            (void *)SetModeTwoAndRefresh, &gEquipmentOtherSlotHelpPrompt, (void *)1);
        break;
    }
    if (opened) {
        work->mode = 1;
        SetFlagGatedElementsVisible(func_ov039_020bc1dc(), FALSE);
    }
    return opened;
}

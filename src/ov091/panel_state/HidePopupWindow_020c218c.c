#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int frameSlot;
} PopupManager;

extern PopupManager *g_popupManager_020c373c;
extern void SetSubBg2Visible_020c271c(void *scene, BOOL visible);
extern void SetPopupSlotVisible_020c1d48(int slotIndex, BOOL visible);
extern void ClosePopupText_020c1ae8(void *window);
extern void SetPopupState_020c2784(void *machine, s32 state);

void HidePopupWindow_020c218c(void *popup)
{
    SetSubBg2Visible_020c271c(popup, FALSE);
    SetPopupSlotVisible_020c1d48(g_popupManager_020c373c->frameSlot, FALSE);
    ClosePopupText_020c1ae8(popup);
    SetPopupState_020c2784(popup, 0);
}

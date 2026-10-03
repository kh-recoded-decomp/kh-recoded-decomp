#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x7fc0 - 4];
    u8 messageWindow[0x1c6f4 - 0x7fc0];
    u32 stateTimer;
} SlotMenu;

extern SlotMenu *data_ov076_020cd3e0;

extern void SlotMenu_ShowSlotHint_020c827c(SlotMenu *menu);
extern void *func_ov039_020bc1bc(void);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);
extern void SlotMenu_LockTouchUntilCommit_020c88dc(SlotMenu *menu, BOOL unused);
extern BOOL MessageWindow_IsFinished_020cbb90(void *window);
extern void SlotMenu_ReturnToBrowse_020c8500(SlotMenu *menu);
extern void SlotMenu_SetReturnCallback_020c89c4(SlotMenu *menu);
extern void SlotMenu_ClearSelectedSlot_020c88b4(SlotMenu *menu);

void SlotMenu_OnMessageConfirm_020c8a70(SlotMenu *menu, BOOL accepted)
{
    switch (menu->state) {
    case 3:
        if (accepted) {
            menu->state = 4;
            return;
        }
        menu->state = 1;
        menu->stateTimer = 0;
        SlotMenu_ShowSlotHint_020c827c(data_ov076_020cd3e0);
        SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), TRUE);
        SlotMenu_LockTouchUntilCommit_020c88dc(menu, FALSE);
        return;
    case 6:
    case 7:
        if (MessageWindow_IsFinished_020cbb90(menu->messageWindow)) {
            SlotMenu_ReturnToBrowse_020c8500(menu);
            return;
        }
        break;
    case 9:
        SlotMenu_SetReturnCallback_020c89c4(menu);
        menu->state = 1;
        menu->stateTimer = 0;
        return;
    case 8:
        if (accepted) {
            SlotMenu_ClearSelectedSlot_020c88b4(menu);
        } else {
            SlotMenu_LockTouchUntilCommit_020c88dc(menu, TRUE);
        }
        menu->state = 1;
        menu->stateTimer = 0;
        SlotMenu_ShowSlotHint_020c827c(data_ov076_020cd3e0);
        SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), TRUE);
        break;
    }
}

#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

typedef BOOL (*SlotMenuCheck)(SlotMenu *menu);
typedef void (*SlotMenuAction)(SlotMenu *menu);

typedef struct ScrollList {
    u8 pad_00[0x34];
    s32 scrollY;
} ScrollList;

struct SlotMenu {
    s32 state;
    BOOL headerShown;
    u8 pad_00008[0x24 - 8];
    u8 touchInput[0x11ee4 - 0x24];
    ScrollList list;
    u8 pad_11F1C[0x1c6f4 - 0x11f1c];
    u32 stateTimer;
};

extern char data_ov076_020cd26c[];
extern char data_ov076_020cd278[];
extern char data_ov076_020cd260[];

extern void *func_ov039_020bc1bc(void);
extern BOOL func_02029f48(void);
extern BOOL func_ov076_020cbba0(void *touch, SlotMenu *menu, SlotMenuCheck check, SlotMenuAction action, void *region, int arg5);
extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);
extern BOOL SlotMenu_HasThreeFilledSlotsAndFlags_020c5248(SlotMenu *menu);
extern BOOL SlotMenu_OpenEmptySlot_020c4f7c(SlotMenu *menu);
extern void SlotMenu_BeginSlotSelection_020c4edc(SlotMenu *menu);
extern void SlotMenu_ShowSlotHint_020c827c(SlotMenu *menu);
extern void func_ov076_020c546c(SlotMenu *menu);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);
extern void ToggleSharedStateFlag_020c1d1c(int flag);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *layout);
extern void SlotMenu_SetBgScrollMode_020c74e4(SlotMenu *menu, int mode, int scrollY);
extern void func_ov076_020c4ca0(SlotMenu *menu);
extern void UpdateWidgetRootAndFireAlarm_020b8c94(void *layout, int arg);
extern void func_ov076_020c7534(SlotMenu *menu, int mode);

void SlotMenu_UpdateBrowse_020c4d94(SlotMenu *menu)
{
    void *layout = func_ov039_020bc1bc();

    if (!func_02029f48()) {
        if (!func_ov076_020cbba0(menu->touchInput, menu, NULL, SlotMenu_ResetToBrowse_020c4ea8, data_ov076_020cd26c, 1) &&
            !func_ov076_020cbba0(menu->touchInput, menu, SlotMenu_HasThreeFilledSlotsAndFlags_020c5248, SlotMenu_ResetToBrowse_020c4ea8, data_ov076_020cd278, 1) &&
            !func_ov076_020cbba0(menu->touchInput, menu, SlotMenu_OpenEmptySlot_020c4f7c, SlotMenu_BeginSlotSelection_020c4edc, data_ov076_020cd260, 1)) {
            menu->state = 1;
            menu->stateTimer = 0;
            SlotMenu_ShowSlotHint_020c827c(menu);
            func_ov076_020c546c(menu);
            return;
        }
        menu->state = 2;
        SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
    }
    if (!menu->headerShown) {
        ToggleSharedStateFlag_020c1d1c(1);
        menu->headerShown = TRUE;
    }
    RefreshScrollListLayout_020be138(&menu->list, layout);
    SlotMenu_SetBgScrollMode_020c74e4(menu, 0, menu->list.scrollY);
    func_ov076_020c4ca0(menu);
    UpdateWidgetRootAndFireAlarm_020b8c94(layout, 0);
    func_ov076_020c7534(menu, 0);
}

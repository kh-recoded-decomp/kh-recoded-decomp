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

extern char sOv076_E_020cd28c[];
extern char sOv076_Na_020cd298[];
extern char data_ov076_020cd280[];

extern void *func_ov039_020bc1dc(void);
extern BOOL func_02029f5c(void);
extern BOOL func_ov076_020cbbc0(void *touch, SlotMenu *menu, SlotMenuCheck check, SlotMenuAction action, void *region, int arg5);
extern void func_ov076_020c4ec8(SlotMenu *menu);
extern BOOL SlotMenu_HasThreeFilledSlotsAndFlags(SlotMenu *menu);
extern BOOL SlotMenu_OpenEmptySlot(SlotMenu *menu);
extern void SlotMenu_BeginSlotSelection(SlotMenu *menu);
extern void SlotMenu_ShowSlotHint(SlotMenu *menu);
extern void SlotMenu_UpdateEditScreen(SlotMenu *menu);
extern void SetNavigationElementsVisible(void *container, BOOL visible);
extern void ToggleSharedStateFlag(int flag);
extern void RefreshScrollListLayout(ScrollList *list, void *layout);
extern void SlotMenu_SetBgScrollMode(SlotMenu *menu, int mode, int scrollY);
extern void func_ov076_020c4cc0(SlotMenu *menu);
extern void UpdateWidgetRootAndFireAlarm(void *layout, int arg);
extern void func_ov076_020c7554(SlotMenu *menu, int mode);

void SlotMenu_UpdateBrowse(SlotMenu *menu)
{
    void *layout = func_ov039_020bc1dc();

    if (!func_02029f5c()) {
        if (!func_ov076_020cbbc0(menu->touchInput, menu, NULL, func_ov076_020c4ec8, sOv076_E_020cd28c, 1) &&
            !func_ov076_020cbbc0(menu->touchInput, menu, SlotMenu_HasThreeFilledSlotsAndFlags, func_ov076_020c4ec8, sOv076_Na_020cd298, 1) &&
            !func_ov076_020cbbc0(menu->touchInput, menu, SlotMenu_OpenEmptySlot, SlotMenu_BeginSlotSelection, data_ov076_020cd280, 1)) {
            menu->state = 1;
            menu->stateTimer = 0;
            SlotMenu_ShowSlotHint(menu);
            SlotMenu_UpdateEditScreen(menu);
            return;
        }
        menu->state = 2;
        SetNavigationElementsVisible(func_ov039_020bc1dc(), FALSE);
    }
    if (!menu->headerShown) {
        ToggleSharedStateFlag(1);
        menu->headerShown = TRUE;
    }
    RefreshScrollListLayout(&menu->list, layout);
    SlotMenu_SetBgScrollMode(menu, 0, menu->list.scrollY);
    func_ov076_020c4cc0(menu);
    UpdateWidgetRootAndFireAlarm(layout, 0);
    func_ov076_020c7554(menu, 0);
}

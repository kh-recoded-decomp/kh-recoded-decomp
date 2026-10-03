#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[4];
    BOOL started;
    u8 pad_0000C[0x24 - 0xc];
    u8 navigation[0x718 - 0x24];
    u8 animation[0x7fc0 - 0x718];
    u8 panel[0x11ee0 - 0x7fc0];
    s32 panelMode;
    u8 pad_11EE4[0x49856 - 0x11ee4];
    u8 animationActive;
} SlotMenu;

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern BOOL AdvanceAnimationTracks_0202ef24(void *animation, int step);
extern void SceneNode_Draw_01ffb12c(void *animation);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern void func_ov039_020bc03c(int value);
extern u32 func_ov039_020bc0d4(void);
extern void *func_ov039_020bc1bc(void);
extern void func_ov076_020cb4a8(void *panel, u32 input);
extern BOOL func_ov076_020c8b28(SlotMenu *menu);
extern int func_ov076_020ccbb0(void *navigation, int mode, BOOL locked);
extern void SlotMenu_ShowPointLimitWarning_020c89a0(SlotMenu *menu);
extern void func_ov076_020c4d94(SlotMenu *menu);
extern void func_ov076_020c4e7c(SlotMenu *menu);
extern void func_ov076_020c546c(SlotMenu *menu);
extern void func_ov076_020c5c0c(SlotMenu *menu);
extern void func_ov076_020c5c14(SlotMenu *menu);
extern void func_ov076_020c5c80(SlotMenu *menu);
extern void func_ov076_020c5cac(SlotMenu *menu);
extern void func_ov076_020c5d10(SlotMenu *menu);
extern void func_ov076_020c5d18(SlotMenu *menu);
extern void func_ov076_020c5d20(SlotMenu *menu);
extern BOOL SlotMenu_HasThreeFilledSlotsAndFlags_020c5248(SlotMenu *menu);
extern BOOL func_ov076_020c4f7c(SlotMenu *menu);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);
extern void func_ov076_020c8178(SlotMenu *menu, int mode);

void SlotMenu_Update_020c4b48(SlotMenu *menu)
{
    BOOL withinLimit;
    int touched;

    if (menu->panelMode != 1) {
        func_ov076_020cb4a8(menu->panel, func_ov039_020bc0d4());
    }
    withinLimit = func_ov076_020c8b28(menu);
    touched = func_ov076_020ccbb0(menu->navigation, 2, withinLimit);
    if (touched >= 0 && touched != 1 && !withinLimit) {
        SlotMenu_ShowPointLimitWarning_020c89a0(menu);
    }
    switch (menu->state) {
    case 0:
        func_ov076_020c4d94(menu);
        break;
    case 2:
        func_ov076_020c4e7c(menu);
        break;
    case 1:
        func_ov076_020c546c(menu);
        break;
    case 3:
        func_ov076_020c5c0c(menu);
        break;
    case 4:
        func_ov076_020c5c14(menu);
        break;
    case 6:
        func_ov076_020c5c80(menu);
        break;
    case 5:
    case 7:
        func_ov076_020c5cac(menu);
        break;
    case 8:
        func_ov076_020c5d10(menu);
        break;
    case 9:
        func_ov076_020c5d18(menu);
        break;
    case 10:
        func_ov076_020c5d20(menu);
        break;
    }
    if (menu->animationActive != 0 && !AdvanceAnimationTracks_0202ef24(menu->animation, 0x1000)) {
        SceneNode_Draw_01ffb12c(menu->animation);
    } else {
        menu->animationActive = 0;
    }
    if (!menu->started) {
        SetStatusPageAndCursor_020c2ca4(1, -1);
        func_ov039_020bc03c(1);
        menu->started = TRUE;
        if (!IsGlobalPackedBitSet_02027304(0xf74) ||
            (!IsGlobalPackedBitSet_02027304(0xfbe) && SlotMenu_HasThreeFilledSlotsAndFlags_020c5248(menu)) ||
            (!IsGlobalPackedBitSet_02027304(0xf75) && func_ov076_020c4f7c(menu))) {
            SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
            func_ov076_020c8178(menu, 0);
        }
    }
}

#include "nitro/types.h"

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    s16 topSlot;
    u8 pad_06;
    u8 visibleCount;
    u8 rowHeight;
    u8 pad_09[3];
    s32 wrapUp;
    s32 wrapDown;
    u8 pad_14[4];
    s32 repeatEnabled;
    u8 pad_1C[2];
    s16 offsetY;
    u8 pad_20[4];
    s16 cursorX;
    s16 cursorWidth;
} ScrollList;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
} SaveData;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x14 - 4];
    u32 column;
    int archiveA;
    int archiveB;
    u8 pad_00020[4];
    u8 panel[0x11c38 - 0x24];
    u16 panelStyle;
    u16 panelWidth;
    u8 pad_11C3C[0x11ee0 - 0x11c3c];
    s32 panelMode;
    ScrollList list;
    u8 pad_11F0C[0x49828 - 0x11f0c];
    s16 hintMessage;
    u8 pad_4982A[2];
    s32 timer;
    s32 pendingSlot;
    u8 pad_49834[0x49855 - 0x49834];
    u8 dragActive;
    u8 pad_49856[2];
    u8 tweenActive;
    u8 pad_49859[0x4a06c - 0x49859];
    s32 guideActive;
    u8 pad_4A070[0x4a104 - 0x4a070];
} SlotMenu;

extern SlotMenu *data_ov076_020cd3e0;
extern SaveData *data_0205fe0c;
extern const char data_ov076_020cd328[];
extern const char data_ov076_020cd33c[];

extern void func_01ff8830(void *dst, int value, u32 size);
extern int func_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern void AcquireRecordManager_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void MenuPanel_Create_020cbccc(void *panel, int owner, void (*onClose)(SlotMenu *menu));
extern void func_ov076_020c8ef0(SlotMenu *menu);
extern void *func_ov039_020bc1bc(void);
extern void func_ov034_020bde84(ScrollList *list, void *layout, int elementId, int arg3, int arg4, int arg5, int arg6,
                                int arg7, int arg8);
extern void ScriptCmd_ResetScreenLayer_020be0c4(ScrollList *list, void *layout);
extern void SetStateFlagBits_020bc688(int flags, int value);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SlotMenu_BuildSlotMasks_020c4260(SlotMenu *menu, int mode, BOOL checkRank);
extern void func_ov076_020c5f5c(SlotMenu *menu);
extern void SlotMenu_InitTouchLayout_020c63b4(SlotMenu *menu);
extern void func_ov076_020c6954(SlotMenu *menu);
extern void SlotMenu_BuildPairMatrix_020c6c40(SlotMenu *menu);
extern void SlotMenu_SelectGuideStep_020c439c(SlotMenu *menu);
extern void SlotMenu_ReloadSlot_020c6f60(SlotMenu *menu, int slot, int mode);

#define REG_POWCNT (*(volatile u16 *)0x04000304)

BOOL SlotMenu_Init_020c45a8(SlotMenu *menu)
{
    void *layout;
    int slot;

    func_01ff8830(menu, 0, sizeof(SlotMenu));
    data_ov076_020cd3e0 = menu;
    REG_POWCNT = REG_POWCNT & ~0x8000;
    menu->archiveA = func_0202cc6c(data_ov076_020cd328, 0xe, 0);
    menu->archiveB = func_0202cc6c(data_ov076_020cd33c, 0xe, 0);
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 0);
    AcquireRecordSlot_02051d3c(1, 0);
    AcquireRecordSlot_02051d3c(5, 0);
    MenuPanel_Create_020cbccc(menu->panel, 1, func_ov076_020c8ef0);
    menu->panelMode = 0;
    menu->panelStyle = 2;
    menu->panelWidth = 4;
    layout = func_ov039_020bc1bc();
    menu->list.count = data_0205fe0c->extraSlotCount + 3;
    menu->list.visibleCount = 2;
    menu->list.rowHeight = 0x40;
    menu->list.offsetY = -0x10;
    menu->list.cursorX = 0x18;
    menu->list.cursorWidth = 0xf0;
    menu->list.wrapDown = 1;
    menu->list.wrapUp = 1;
    menu->list.repeatEnabled = 1;
    func_ov034_020bde84(&menu->list, layout, 0x75, 100, 0xe, 1, 0x40, 1, 0);
    ScriptCmd_ResetScreenLayer_020be0c4(&menu->list, layout);
    SetStateFlagBits_020bc688(1, 0);
    menu->column = 0;
    menu->hintMessage = -1;
    if (!IsGlobalPackedBitSet_02027304(0xf50) && IsGlobalPackedBitSet_02027304(0xf75)) {
        SlotMenu_BuildSlotMasks_020c4260(menu, 0, FALSE);
        menu->guideActive = 1;
    }
    func_ov076_020c5f5c(menu);
    SlotMenu_InitTouchLayout_020c63b4(menu);
    func_ov076_020c6954(menu);
    SlotMenu_BuildPairMatrix_020c6c40(menu);
    SlotMenu_SelectGuideStep_020c439c(menu);
    for (slot = 0; slot < menu->list.count; slot++) {
        SlotMenu_ReloadSlot_020c6f60(menu, slot, 0);
    }
    menu->state = 0;
    menu->timer = 0;
    menu->pendingSlot = -1;
    menu->dragActive = 0;
    menu->tweenActive = 0;
    return TRUE;
}

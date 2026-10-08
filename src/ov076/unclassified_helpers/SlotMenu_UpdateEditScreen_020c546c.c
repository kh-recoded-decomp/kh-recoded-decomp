#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SlotPair0Entry {
    u8 pad_00[0x20];
    int pair1Index;
} SlotPair0Entry;

typedef struct SlotPair1Entry {
    u8 pad_00[0x1e];
    u16 iconId;
} SlotPair1Entry;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
    u8 pad_2C69[0x2d84 - 0x2c69];
    u16 slotHandles[16];
} SaveData;

typedef struct StockItem {
    u32 handle;
    u32 kind;
} StockItem;

typedef struct StockEntry {
    u16 count;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    StockItem *item;
} StockEntry;

typedef struct CursorMarker {
    u8 pad_00[0xc];
} CursorMarker;

typedef struct PadState {
    u8 pad_00[8];
    u16 held;
} PadState;

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    s16 topSlot;
    u8 pad_06[0x20 - 6];
    s16 touchSlot;
    u8 pad_22[0x34 - 0x22];
    s32 scrollY;
} ScrollList;

typedef struct SlotMenu {
    s32 state;
    BOOL headerShown;
    u8 pad_00008[8];
    BOOL touchArmed;
    u32 column;
    u8 pad_00018[0xc];
    u8 panel[8];
    s32 panelLayer;
    u8 pad_00030[0x3c3c - 0x30];
    StockEntry *stockEntries[(0x4daa - 0x3c3c) / 4];
    u8 pad_04DA8[2];
    s16 stockIndex;
    u8 pad_04DAC[0x7fc0 - 0x4dac];
    s32 windowMode;
    u8 pad_07FC4[0x11ee0 - 0x7fc4];
    s32 panelMode;
    ScrollList list;
    u8 pad_11F1C[0x1c6f4 - 0x11f1c];
    u32 stateTimer;
    u8 pad_1C6F8[0x49828 - 0x1c6f8];
    s16 iconId;
    u8 pad_4982A[2];
    s32 windowLayer;
    s32 hintSlot;
    u8 pad_49834[0x49858 - 0x49834];
    u8 scrollMode;
    u8 pad_49859[0x4a068 - 0x49859];
    s32 altView;
    BOOL pendingUnlock;
    BOOL retryCombine;
    BOOL showTutorial;
} SlotMenu;

extern SaveData *data_0205fe0c;
extern CursorMarker data_ov076_020cd284;
extern CursorMarker data_ov076_020cd290;
extern CursorMarker data_ov076_020cd29c;
extern CursorMarker data_ov076_020cd2a8;
extern CursorMarker data_ov076_020cd2b4;
extern CursorMarker data_ov076_020cd2c0;
extern CursorMarker data_ov076_020cd2cc;
extern CursorMarker data_ov076_020cd2d8;

extern void *func_ov039_020bc1bc(void);
extern BOOL func_ov039_020bc0d4(void);
extern PadState *func_ov039_020bca00(void);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void SetupStageParams_020bdf10(ScrollList *list, void *layout, int mode);
extern void ToggleSharedStateFlag_020c1d1c(int flag);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern BOOL ResolveMergedRecordEntry_020295c8(int index, RecordEntry *entry, u32 *outValue);
extern SlotPair0Entry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern SlotPair1Entry *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void UpdateWidgetRootAndResetList_020b8c80(void *layout, int arg);
extern void UpdateWidgetRootAndFireAlarm_020b8c94(void *layout, int arg);
extern BOOL SlotMenu_IsPanelModeUnchanged_020c7188(SlotMenu *menu);
extern void SlotMenu_SelectGuideStep_020c439c(SlotMenu *menu);
extern void SlotMenu_LoadCursorSlotRecord_020c4444(SlotMenu *menu);
extern BOOL SlotMenu_CanCombineSlotPair_020c44c0(SlotMenu *menu, int slot);
extern BOOL SlotMenu_HandleSlotTouch_020c480c(SlotMenu *menu);
extern void SlotMenu_HandleColumnInput_020c4894(SlotMenu *menu);
extern void SlotMenu_ToggleStockInSlot_020c4a90(SlotMenu *menu);
extern void func_ov076_020c4ca0(SlotMenu *menu);
extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);
extern void SlotMenu_OpenConfirmPrompt_020c4f18(SlotMenu *menu);
extern void SlotMenu_EnterSlotView_020c4f34(SlotMenu *menu);
extern BOOL SlotMenu_IsThirdColumnMarked_020c5190(SlotMenu *menu);
extern BOOL SlotMenu_IsSecondColumnMarked_020c51b0(SlotMenu *menu);
extern BOOL func_ov076_020c51cc(SlotMenu *menu);
extern BOOL SlotMenu_IsPointTotalOverLimit_020c52d0(SlotMenu *menu);
extern void SlotMenu_MoveCursorToSlot_020c52f8(SlotMenu *menu, u16 slot, u16 column, int mode, CursorMarker *cursor);
extern void SlotMenu_UpdatePairedCategory_020c53c8(SlotMenu *menu);
extern BOOL SlotMenu_CheckPointLimit_020c544c(SlotMenu *menu, BOOL showWarning);
extern void PXI_Init_020c5c0c(SlotMenu *menu);
extern void SlotMenu_ReloadSlot_020c6f60(SlotMenu *menu, int slot, int mode);
extern void SlotMenu_ReloadVisibleSlots_020c7144(SlotMenu *menu);
extern void SlotMenu_UpdateItemSprites_020c7254(SlotMenu *menu, int mode, int scrollY);
extern void SlotMenu_SetBgScrollMode_020c74e4(SlotMenu *menu, int mode, int scrollY);
extern void func_ov076_020c7534(SlotMenu *menu, int mode);
extern void func_ov076_020c7a5c(SlotMenu *menu, int mode);
extern void SlotMenu_ShowSlotHint_020c827c(SlotMenu *menu);
extern void SlotMenu_OpenSlotMessage_020c8388(SlotMenu *menu, int messageId);
extern BOOL MessageWindow_IsFinished_020cbb90(void *window);
extern BOOL func_ov076_020cbba0(void *panel, SlotMenu *owner, BOOL (*check)(SlotMenu *), void (*action)(SlotMenu *), CursorMarker *cursor, int style);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);

void SlotMenu_UpdateEditScreen_020c546c(SlotMenu *menu);

static inline void SetWindow1InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04000048 & ~0x3f00) | (planeMask << 8);
    if (effect) {
        value |= 0x2000;
    }
    *(vu16 *)0x04000048 = (u16)value;
}

static inline BOOL SlotMenu_SyncAltView(SlotMenu *menu)
{
    if (menu->altView != menu->panelLayer) {
        menu->altView ^= 1;
        return TRUE;
    }
    return FALSE;
}

static inline BOOL IsStockKindUsable(u32 kind)
{
    BOOL usable = FALSE;
    if (kind <= 3 && ((1 << kind) & 0xd)) {
        usable = TRUE;
    }
    return usable;
}

static inline BOOL IsStockEntryUsable(u16 count, u16 used, u32 kind)
{
    BOOL kindOk;
    BOOL usable = FALSE;
    if (count > used) {
        kindOk = FALSE;
        if (IsStockKindUsable(kind)) {
            kindOk = TRUE;
        }
        if (kindOk) {
            usable = TRUE;
        }
    }
    return usable;
}

static inline BOOL IsTouchIdle(void)
{
    if (func_ov039_020bc0d4()) {
        return FALSE;
    }
    return TRUE;
}

void SlotMenu_UpdateEditScreen_020c546c(SlotMenu *menu)
{
    void *layout = func_ov039_020bc1bc();
    int mode;
    s16 prevTop;

    if (!menu->headerShown) {
        ToggleSharedStateFlag_020c1d1c(1);
        menu->headerShown = TRUE;
    }
    if (!SlotMenu_IsPanelModeUnchanged_020c7188(menu)) {
        switch (menu->panelMode) {
        case 0:
            SetStateFlagBits_020bc688(1, 0);
            SetupStageParams_020bdf10(&menu->list, layout, 1);
            *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1d00;
            *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x90;
            MIi_CpuClearFast_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x600);
            menu->stateTimer = 0;
            menu->iconId = -1;
            SlotMenu_CheckPointLimit_020c544c(menu, FALSE);
            SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, menu->column, 1, &data_ov076_020cd29c);
            SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, menu->column, 1, &data_ov076_020cd2a8);
            if (func_ov076_020cbba0(menu->panel, menu, SlotMenu_IsPointTotalOverLimit_020c52d0, SlotMenu_ResetToBrowse_020c4ea8, &data_ov076_020cd284, 1)) {
                menu->state = 2;
                SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
            } else if (menu->retryCombine && func_ov076_020cbba0(menu->panel, menu, func_ov076_020c51cc, SlotMenu_ResetToBrowse_020c4ea8, &data_ov076_020cd29c, 2)) {
                menu->state = 2;
                SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
            } else {
                SlotMenu_ShowSlotHint_020c827c(menu);
            }
            menu->retryCombine = FALSE;
            break;
        case 1:
            SetupStageParams_020bdf10(&menu->list, layout, 0);
            *(vu16 *)0x04000042 = 0x4000;
            *(vu16 *)0x04000046 = 0xb0c0;
            SetWindow1InsidePlane(0x18, TRUE);
            menu->windowLayer = 2;
            if (menu->pendingUnlock) {
                SetGlobalPackedBit_02027320(0xf50);
                menu->pendingUnlock = FALSE;
            }
            break;
        case 2:
            SlotMenu_ToggleStockInSlot_020c4a90(menu);
        case 3:
            SlotMenu_SelectGuideStep_020c439c(menu);
            SlotMenu_ReloadSlot_020c6f60(menu, menu->list.slotIndex, 0);
            if (!SlotMenu_IsPointTotalOverLimit_020c52d0(menu)) {
                SlotMenu_ShowSlotHint_020c827c(menu);
            }
            *(vu16 *)0x04000042 = 0x4000;
            *(vu16 *)0x04000046 = 0xa8c0;
            SetWindow1InsidePlane(0x08, TRUE);
            func_ov076_020c7a5c(menu, 0);
            SlotMenu_UpdateItemSprites_020c7254(menu, 0, menu->list.scrollY);
            *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x90;
            break;
        }
    } else if (SlotMenu_SyncAltView(menu)) {
        if (menu->altView) {
            int slot = 0;
            int count = data_0205fe0c->extraSlotCount + 3;
            *(vu16 *)0x04000042 = 0x4000;
            *(vu16 *)0x04000046 = 0xa8c0;
            SetWindow1InsidePlane(0x08, TRUE);
            for (; slot < count; slot++) {
                if (data_0205fe0c->slotHandles[slot * 2] < 0x200) {
                    SlotMenu_ReloadSlot_020c6f60(menu, slot, 0);
                }
            }
        } else {
            *(vu16 *)0x04000042 = 0x4000;
            *(vu16 *)0x04000046 = 0xb0c0;
            SetWindow1InsidePlane(0x18, TRUE);
        }
    }

    if (!func_ov039_020bc0d4()) {
        SlotMenu_SelectGuideStep_020c439c(menu);
        if (menu->column != 0) {
            u16 handle = data_0205fe0c->slotHandles[menu->list.slotIndex * 2 + menu->column - 1];
            if (handle == 0xffff || handle < 0x200) {
                menu->column = 0;
                SlotMenu_SetBgScrollMode_020c74e4(menu, menu->panelMode == 1, menu->list.scrollY);
            }
        }
    }
    if (menu->altView == 0 && menu->panelMode == 1) {
        SetupStageParams_020bdf10(&menu->list, layout, 0);
    }
    if (menu->altView != 0) {
        SlotMenu_SetBgScrollMode_020c74e4(menu, menu->panelMode == 1 && menu->altView == 0, menu->list.scrollY);
        func_ov076_020c7534(menu, 0);
        if (menu->panelMode == 1) {
            SetupStageParams_020bdf10(&menu->list, layout, 1);
        }
    } else {
        mode = menu->panelMode;
        if (mode == 0) {
            prevTop = menu->list.topSlot;
            if (!MessageWindow_IsFinished_020cbb90(&menu->windowMode)) {
                func_ov076_020c7534(menu, 0);
                return;
            }
            if (!IsTouchIdle()) {
                u16 held = func_ov039_020bca00()->held;
                if (menu->panelMode == 0 && (held & 3) == 1) {
                    menu->touchArmed = TRUE;
                } else if (menu->touchArmed && (held & 7) == 4 && menu->list.touchSlot >= 0) {
                    menu->touchArmed = FALSE;
                    if (SlotMenu_HandleSlotTouch_020c480c(menu)) {
                        menu->list.touchSlot = -1;
                        menu->hintSlot = -1;
                        if (menu->column == 2) {
                            if (SlotMenu_CanCombineSlotPair_020c44c0(menu, menu->list.slotIndex)) {
                                SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, menu->column, 0, &data_ov076_020cd2b4);
                                SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, menu->column, 0, &data_ov076_020cd2c0);
                                if (func_ov076_020cbba0(menu->panel, menu, SlotMenu_IsThirdColumnMarked_020c5190, SlotMenu_OpenConfirmPrompt_020c4f18, &data_ov076_020cd2b4, 2)) {
                                    menu->state = 2;
                                    SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
                                    menu->showTutorial = TRUE;
                                    PlaySoundEffect_0204d924(1, 1);
                                    SlotMenu_UpdateEditScreen_020c546c(menu);
                                    return;
                                }
                                SlotMenu_OpenSlotMessage_020c8388(menu, 0x27);
                                menu->state = 3;
                                SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
                                PXI_Init_020c5c0c(menu);
                                return;
                            }
                            PlaySoundEffect_0204d924(1, 4);
                        } else {
                            SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, menu->column, 0, &data_ov076_020cd290);
                            SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, 0, 0, &data_ov076_020cd2cc);
                            SlotMenu_MoveCursorToSlot_020c52f8(menu, menu->list.slotIndex, 0, 0, &data_ov076_020cd2d8);
                            if (func_ov076_020cbba0(menu->panel, menu, SlotMenu_IsSecondColumnMarked_020c51b0, SlotMenu_EnterSlotView_020c4f34, &data_ov076_020cd290, 1)) {
                                menu->state = 2;
                                SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
                                PlaySoundEffect_0204d924(1, 1);
                                SlotMenu_UpdateEditScreen_020c546c(menu);
                                return;
                            }
                            *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x10;
                            SlotMenu_LoadCursorSlotRecord_020c4444(menu);
                            SlotMenu_UpdatePairedCategory_020c53c8(menu);
                            *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
                            SlotMenu_UpdateEditScreen_020c546c(menu);
                            return;
                        }
                    } else {
                        SlotMenu_ShowSlotHint_020c827c(menu);
                    }
                }
                SlotMenu_SetBgScrollMode_020c74e4(menu, 0, menu->list.scrollY);
                SlotMenu_HandleColumnInput_020c4894(menu);
                menu->hintSlot = menu->list.slotIndex;
                func_ov076_020c4ca0(menu);
            } else {
                SlotMenu_SetBgScrollMode_020c74e4(menu, 0, menu->list.scrollY);
                SlotMenu_ShowSlotHint_020c827c(menu);
            }
            UpdateWidgetRootAndFireAlarm_020b8c94(layout, 0);
            if (menu->list.topSlot != prevTop) {
                SlotMenu_ReloadVisibleSlots_020c7144(menu);
            }
            func_ov076_020c7534(menu, 0);
        } else if (mode == 1) {
            StockEntry *entry = menu->stockEntries[menu->stockIndex];
            BOOL scrollMode = menu->windowMode == 4;
            BOOL found = FALSE;
            if (entry != NULL && IsStockEntryUsable(entry->count, entry->used, entry->item->kind)) {
                found = TRUE;
            }
            if (!found) {
                menu->iconId = -1;
            } else {
                int slot = menu->list.slotIndex;
                u32 column = menu->column;
                int pair = slot * 2;
                u16 first = data_0205fe0c->slotHandles[pair];
                u16 second = data_0205fe0c->slotHandles[pair + 1];
                u32 value;
                RecordEntry record;
                SlotPair0Entry *pair0;
                if (entry->item->kind == 0) {
                    data_0205fe0c->slotHandles[pair] = entry->item->handle;
                    data_0205fe0c->slotHandles[pair + 1] = 0xffff;
                } else {
                    data_0205fe0c->slotHandles[column + pair] = entry->recordIndex + 0x200;
                }
                ResolveMergedRecordEntry_020295c8(slot, &record, &value);
                pair0 = GetRecordSlotPair0Entry_02051ec8(record.active == 1 ? (u8)record.category : value);
                menu->iconId = GetRecordSlotPair1Entry_02051ef4(pair0->pair1Index)->iconId;
                data_0205fe0c->slotHandles[pair] = first;
                data_0205fe0c->slotHandles[pair + 1] = second;
            }
            func_ov076_020c7534(menu, 1);
            if (menu->scrollMode != scrollMode) {
                SlotMenu_SetBgScrollMode_020c74e4(menu, scrollMode, menu->list.scrollY);
            }
        } else {
            func_ov076_020c7534(menu, mode == 1);
        }
    }
    if (menu->altView) {
        UpdateWidgetRootAndResetList_020b8c80(func_ov039_020bc1bc(), 0);
    }
    if (++menu->stateTimer >= 0x1e) {
        menu->stateTimer = 0;
    }
}

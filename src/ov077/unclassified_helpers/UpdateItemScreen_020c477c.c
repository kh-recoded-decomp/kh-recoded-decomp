#include "nitro/types.h"

#pragma opt_propagation off

typedef struct ItemDef {
    s32 handle;
    s32 category;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    u8 pad_04[4];
    ItemDef *def;
} ItemStock;

typedef struct ParamBlock {
    u8 pad_00[0xa];
    u16 value;
    s32 word;
} ParamBlock;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 flag;
} OverlaySelectionRecord;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 partySlots[8];
} SaveState;

typedef struct ItemScreen {
    s32 unk_00;
    s32 unk_04;
    s32 started;
    u8 pad_0000c[8];
    u8 tabs[8];
    s32 tabMode;
    u8 pad_00020[0xc];
    void *container;
    u8 pad_00030[0x80c - 0x30];
    ItemStock slots[(0x3c2c - 0x80c) / 12];
    ItemStock *stocks[(0x4d9a - 0x3c2c) / 4];
    u8 pad_04d98[2];
    s16 cursorIndex;
    u8 pad_04d9c[0x7fb0 - 0x4d9c];
    s32 windowState;
    u8 pad_07fb4[0x11ed0 - 0x7fb4];
    s32 mode;
    u8 pad_11ed4[0x11ff4 - 0x11ed4];
    s32 state;
    s32 slot;
    s32 initialized;
    s32 cameraLocked;
    u8 pad_12004[0x14d04 - 0x12004];
    ItemStock *lastStock;
    ItemStock *equipped;
    u16 maxValue;
    u8 pad_14d0e[2];
    s32 paramWord;
    s32 pending;
    s32 touchLatch;
    s32 selectionFlag;
    s32 recordId;
    u16 entries[3];
    u16 lastTab;
} ItemScreen;

extern SaveState *data_0205fe0c;
extern void ToggleSharedStateFlag_020c1d1c(BOOL enable);
extern BOOL func_ov039_020bc0d4(void);
extern BOOL func_ov039_020bc0ec(void);
extern void func_ov039_020bc03c(int value);
extern void *func_ov039_020bc1bc(void);
extern void MessageWindow_Update_020c84dc(void *window, BOOL handleInput);
extern int TabBar_HandleTouch_020c9be4(void *owner, int currentTab, BOOL enabled);
extern void OpenHelpMessageOrActivate_020c4b50(ItemScreen *screen);
extern void func_ov077_020c4bac(ItemScreen *screen);
extern void UpdateItemScreenDisplay_020c4be0(ItemScreen *screen);
extern ParamBlock *func_020505a8(void);
extern BOOL func_ov077_020c43f8(ItemScreen *screen);
extern void BeginSlotItemSelection_020c5cc8(ItemScreen *screen);
extern void MoveSlotCursor_020c4514(ItemScreen *screen);
extern void ShowSlotItemHeader_020c437c(ItemScreen *screen);
extern void SetPanelShifted_020c5618(ItemScreen *screen, BOOL shifted);
extern void ResetMenuCamera_020c5648(ItemScreen *screen, int mode);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetFlagGatedElementsVisible_020c9d7c(void *container, BOOL visible);
extern void func_ov077_020c5944(ItemScreen *screen, void *text);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern int func_ov027_020b965c(void *container, void *widget);
extern void ShowStatusRecordList_020c2b10(u16 *entries);
extern void OpenStatusRecordList_020c2a04(u32 recordId);
extern void SetSharedListMode_020c2aec(int mode);
extern void SetSharedListEntries_020c2c24(const u16 *ids);
extern void SetSharedListBusy_020c2c44(BOOL busy);
extern void SyncSharedListScroll_020c2ac8(void);
extern OverlaySelectionRecord *func_0204f768(u32 index);
extern void TrackMaxParamValue_020c4260(ItemScreen *screen);
extern void SetParamHalf18_02050630(u16 value);
extern void SetParamWord20_02050640(int value);

static inline u16 GetPartySlot(int i)
{
    switch (i) {
    case 0:
        return data_0205fe0c->partySlots[0];
    case 1:
        return data_0205fe0c->partySlots[1];
    default:
        if (i >= 2 && i < data_0205fe0c->extraSlotCount + 3) {
            return data_0205fe0c->partySlots[i];
        }
        return 0xffff;
    }
}

static inline BOOL IsInputIdle(void)
{
    return !func_ov039_020bc0d4();
}

void UpdateItemScreen_020c477c(ItemScreen *screen)
{
    if (!screen->initialized) {
        ToggleSharedStateFlag_020c1d1c(TRUE);
        screen->initialized = TRUE;
    }
    if (screen->mode != 1) {
        MessageWindow_Update_020c84dc(&screen->windowState, func_ov039_020bc0d4());
    }
    TabBar_HandleTouch_020c9be4(screen->tabs, 3, TRUE);
    switch (screen->state) {
    case 0:
        OpenHelpMessageOrActivate_020c4b50(screen);
        break;
    case 1:
        func_ov077_020c4bac(screen);
        break;
    case 2:
        UpdateItemScreenDisplay_020c4be0(screen);
        break;
    }
    if (screen->pending != 0 && func_020505a8()->value > screen->maxValue) {
        screen->maxValue = func_020505a8()->value;
    }
    if (screen->mode == 0 && !IsInputIdle()) {
        if (screen->windowState == 4 && screen->state != 0) {
            if (func_ov077_020c43f8(screen)) {
                BeginSlotItemSelection_020c5cc8(screen);
                UpdateItemScreen_020c477c(screen);
                return;
            }
            MoveSlotCursor_020c4514(screen);
        }
        ShowSlotItemHeader_020c437c(screen);
        SetPanelShifted_020c5618(screen, FALSE);
    }
    ResetMenuCamera_020c5648(screen, screen->mode == 1 && screen->cameraLocked == 0);
    if (!screen->started) {
        SetStatusPageAndCursor_020c2ca4(4, -1);
        func_ov039_020bc03c(1);
        screen->started = TRUE;
        if (!IsGlobalPackedBitSet_02027304(0xf92)) {
            SetFlagGatedElementsVisible_020c9d7c(func_ov039_020bc1bc(), FALSE);
            func_ov077_020c5944(screen, NULL);
        }
    }
    if (screen->slot == 0) {
        void *container = screen->container;
        ItemStock *stock = screen->stocks[screen->cursorIndex];
        BOOL equippedChanged = FALSE;
        ParamBlock *params;
        int tab = func_ov027_020b965c(container, FindWidgetById_020b90a4(container, 0x1b));

        if (screen->touchLatch != 0 && func_ov039_020bc0d4()) {
            if (screen->equipped != NULL && screen->lastStock != NULL
                && screen->equipped->def->handle == screen->lastStock->def->handle) {
                ShowStatusRecordList_020c2b10(screen->entries);
            }
            screen->touchLatch = 0;
        } else if (screen->touchLatch == 0 && func_ov039_020bc0ec()) {
            screen->touchLatch = 1;
        }
        if (screen->tabMode != 0 && tab != screen->lastTab) {
            if (screen->lastTab == 0 || screen->lastTab == 1 || screen->lastTab == 6) {
                if (tab != 0 && tab != 1 && tab != 6 && screen->pending != 0) {
                    func_0204f768(0)->flag = screen->selectionFlag;
                    TrackMaxParamValue_020c4260(screen);
                    SetParamWord20_02050640(screen->paramWord);
                    OpenStatusRecordList_020c2a04(screen->recordId);
                    SetSharedListEntries_020c2c24(screen->entries);
                    SetSharedListBusy_020c2c44(FALSE);
                    SyncSharedListScroll_020c2ac8();
                    screen->pending = 0;
                }
            } else if (tab == 0 || tab == 1 || tab == 6) {
                params = func_020505a8();

                screen->equipped = &screen->slots[GetPartySlot(0)];
                if (screen->pending == 0) {
                    ShowStatusRecordList_020c2b10(screen->entries);
                    if (screen->entries[1] != 0) {
                        screen->maxValue = params->value;
                        screen->paramWord = params->word;
                        screen->selectionFlag = (screen->equipped->def->handle - 0xd0) % 5;
                        screen->recordId = (screen->equipped->def->handle - 0xd0) / 5;
                        screen->lastStock = NULL;
                        screen->pending = 1;
                    }
                }
            }
        } else {
            if (stock != NULL && stock->def->category == 4
                && (screen->lastStock == NULL || stock->def->handle != screen->lastStock->def->handle)) {
                int key;
                int group;
                int mode;

                if (stock->def->handle == screen->equipped->def->handle) {
                    func_0204f768(0)->flag = screen->selectionFlag;
                    TrackMaxParamValue_020c4260(screen);
                    SetParamWord20_02050640(screen->paramWord);
                    equippedChanged = TRUE;
                } else if (screen->pending == 0) {
                    SetParamHalf18_02050630(0);
                    SetParamWord20_02050640(0);
                }
                key = stock->def->handle - 0xd0;
                group = key / 5;
                mode = key % 5;
                func_0204f768(0)->flag = mode;
                if (screen->lastStock == NULL) {
                    OpenStatusRecordList_020c2a04(group);
                } else if (group != (screen->lastStock->def->handle - 0xd0) / 5) {
                    OpenStatusRecordList_020c2a04(group);
                } else {
                    SetSharedListMode_020c2aec(mode);
                }
                if (equippedChanged) {
                    SetSharedListEntries_020c2c24(screen->entries);
                    SetSharedListBusy_020c2c44(FALSE);
                    SyncSharedListScroll_020c2ac8();
                } else {
                    SetSharedListBusy_020c2c44(TRUE);
                }
                screen->lastStock = stock;
            }
        }
        screen->lastTab = tab;
    }
}

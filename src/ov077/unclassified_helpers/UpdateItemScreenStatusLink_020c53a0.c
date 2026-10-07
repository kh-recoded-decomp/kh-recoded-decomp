#include "nitro/types.h"

#pragma opt_propagation off

typedef struct ItemInfo {
    s32 id;
} ItemInfo;

typedef struct ItemSlotEntry {
    u8 pad_00[0x8];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct StatusRecordList {
    u16 unk_00;
    u16 count;
    u8 pad_04[0x2];
    s16 widgetLayer;
} StatusRecordList;

typedef struct ParamBlock {
    u8 pad_00[0xa];
    u16 value;
    u32 word;
} ParamBlock;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 page;
} OverlaySelectionRecord;

typedef struct ItemScreen {
    u8 pad_00000[0x14];
    u8 panel[0x2c - 0x14];
    void *container;
    u8 pad_00030[0x80c - 0x30];
    ItemSlotEntry slots[0x5d0];
    u8 pad_4dcc[0x11ed0 - 0x4dcc];
    s32 panelState;
    u8 pad_11ed4[0x11ff8 - 0x11ed4];
    s32 tab;
    u8 pad_11ffc[0x14d04 - 0x11ffc];
    s32 statusPending;
    ItemSlotEntry *selectedSlot;
    u16 savedValue;
    u16 pad_14d0e;
    u32 savedWord;
    s32 statusOpen;
    u8 pad_14d18[0x4];
    s32 statusColumn;
    s32 statusRow;
    StatusRecordList statusList;
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 partySlots[8];
} SaveState;

extern SaveState *data_0205fe0c;
extern BOOL func_ov039_020bc0d4(void);
extern int func_ov077_020c9370(void *panel);
extern ParamBlock *func_020505a8(void);
extern void ShowStatusRecordList_020c2b10(StatusRecordList *list);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern s16 func_ov027_020b965c(void *container, void *widget);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void TrackMaxParamValue_020c4260(ItemScreen *screen);
extern void SetParamWord20_02050640(u32 value);
extern void OpenStatusRecordList_020c2a04(int row);
extern void SetSharedListEntries_020c2c24(StatusRecordList *list);
extern void SetSharedListBusy_020c2c44(int busy);
extern void SyncSharedListScroll_020c2ac8(void);

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

BOOL UpdateItemScreenStatusLink_020c53a0(ItemScreen *screen)
{
    void *container = screen->container;
    ParamBlock *params;
    int state;
    int slot;

    if (!func_ov039_020bc0d4()) {
        return TRUE;
    }
    state = func_ov077_020c9370(screen->panel);
    if (screen->panelState == state) {
        return TRUE;
    }
    switch (state) {
    case 1:
        if (screen->tab == 0) {
            params = func_020505a8();
            screen->selectedSlot = &screen->slots[GetPartySlot(0)];
            if (screen->statusOpen == 0) {
                ShowStatusRecordList_020c2b10(&screen->statusList);
                if (screen->statusList.count != 0) {
                    screen->savedValue = params->value;
                    screen->savedWord = params->word;
                    screen->statusColumn = (screen->selectedSlot->info->id - 0xd0) % 5;
                    screen->statusRow = (screen->selectedSlot->info->id - 0xd0) / 5;
                    screen->statusOpen = 1;
                    screen->statusPending = 0;
                    screen->statusList.widgetLayer =
                        func_ov027_020b965c(container, FindWidgetById_020b90a4(container, 0x1b));
                }
            }
        }
        break;
    case 3:
        if (screen->tab == 0 && screen->statusOpen != 0) {
            GetOverlaySelectionRecord_0204f768(0)->page = screen->statusColumn;
            TrackMaxParamValue_020c4260(screen);
            SetParamWord20_02050640(screen->savedWord);
            OpenStatusRecordList_020c2a04(screen->statusRow);
            SetSharedListEntries_020c2c24(&screen->statusList);
            SetSharedListBusy_020c2c44(0);
            SyncSharedListScroll_020c2ac8();
            screen->statusOpen = 0;
        }
        break;
    }
    screen->panelState = state;
    return FALSE;
}

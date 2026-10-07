#include "nitro/types.h"

#pragma opt_propagation off

typedef struct ItemDef {
    s32 handle;
    u8 pad_04[0x1c];
    s32 statusIndex;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    u8 pad_04[4];
    ItemDef *def;
} ItemStock;

typedef struct ItemScreen {
    u8 pad_00000[0x80c];
    ItemStock slots[(0x3c2c - 0x80c) / 12];
    ItemStock *stocks[(0x4d9a - 0x3c2c) / 4];
    u8 pad_04d98[2];
    s16 cursorIndex;
    u8 pad_04d9c[0x11ff8 - 0x4d9c];
    s32 slot;
    u8 pad_11ffc[0x14d08 - 0x11ffc];
    ItemStock *equipped;
    u8 pad_14d0c[4];
    s32 paramWord;
    s32 pending;
    u8 pad_14d18[4];
    s32 selectionFlag;
    u8 pad_14d20[4];
    u16 entries[1];
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 partySlots[8];
} SaveState;

typedef struct SaveParams {
    u32 words[6];
} SaveParams;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 flag;
} OverlaySelectionRecord;

extern SaveState *data_0205fe0c;
extern const SaveParams data_ov077_020ca108;
extern OverlaySelectionRecord *func_0204f768(u32 index);
extern void SetParamHalf18_02050630(u16 value);
extern void SetParamWord20_02050640(int value);
extern void func_ov073_020c1eb4(SaveState *save, const SaveParams *params);
extern void OpenStatusRecordList_020c2a04(u32 recordId);
extern void SyncSharedListScroll_020c2ac8(void);
extern void SetSharedListEntries_020c2c24(const u16 *ids);
extern void SetSharedListBusy_020c2c44(BOOL busy);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern void TrackMaxParamValue_020c4260(ItemScreen *screen);
extern void UpdateItemCountDigits_020c52a0(ItemScreen *screen);
extern void DrawPartySlotLabel_020c5a4c(ItemScreen *screen, int slot);

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

static inline void SetPartySlot(int i, u16 value)
{
    switch (i) {
    case 0:
        data_0205fe0c->partySlots[0] = value;
        break;
    case 1:
        data_0205fe0c->partySlots[1] = value;
        break;
    default:
        if (i >= 2 && i < data_0205fe0c->extraSlotCount + 3) {
            SaveParams params = data_ov077_020ca108;
            data_0205fe0c->partySlots[i] = value;
            func_ov073_020c1eb4(data_0205fe0c, &params);
        }
        break;
    }
}

static inline ItemStock *GetSlotStock(ItemScreen *screen, int index)
{
    return index + screen->slots;
}

void AssignCursorItemToPartySlot_020c4598(ItemScreen *screen)
{
    ItemStock *stock = screen->stocks[screen->cursorIndex];
    u16 current = GetPartySlot(screen->slot);
    OverlaySelectionRecord *record;

    if (current == stock->def->handle) {
        return;
    }
    if (current != 0xffff) {
        GetSlotStock(screen, current)->used--;
    }
    SetPartySlot(screen->slot, stock->def->handle);
    GetSlotStock(screen, stock->def->handle)->used++;
    if (screen->slot == 0) {
        record = func_0204f768(0);
        record->flag = (stock->def->handle - 0xd0) % 5;
        if (screen->equipped->def->handle == stock->def->handle) {
            func_0204f768(0)->flag = screen->selectionFlag;
            TrackMaxParamValue_020c4260(screen);
            SetParamWord20_02050640(screen->paramWord);
        } else {
            SetParamHalf18_02050630(0);
            SetParamWord20_02050640(0);
        }
        OpenStatusRecordList_020c2a04((stock->def->handle - 0xd0) / 5);
        if (screen->equipped->def->handle == stock->def->handle) {
            SetSharedListEntries_020c2c24(screen->entries);
        }
        SetSharedListBusy_020c2c44(FALSE);
        SyncSharedListScroll_020c2ac8();
        screen->pending = 0;
        UpdateItemCountDigits_020c52a0(screen);
    } else if (screen->slot == 1) {
        SetParamHalf18_02050630(0);
        SetParamWord20_02050640(0);
        SyncSharedListScroll_020c2ac8();
    } else if (screen->slot > 1) {
        SetStatusPageAndCursor_020c2ca4(2, stock->def->statusIndex);
    }
    DrawPartySlotLabel_020c5a4c(screen, screen->slot);
}

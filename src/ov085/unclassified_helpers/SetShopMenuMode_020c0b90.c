#pragma opt_dead_assignments off
#include "nitro/types.h"

typedef struct ItemInfo {
    int id;
} ItemInfo;

typedef struct ItemEntry {
    u16 total;
    u16 used;
    u16 recordId;
    u16 pad_06;
    ItemInfo *info;
} ItemEntry;

typedef struct ShopInfo {
    int recordId;
    u8 pad_04[3];
    u8 stockLimit;
    u32 price;
} ShopInfo;

typedef struct OwnedEntry {
    u8 *count;
    ItemEntry *entry;
    ShopInfo *shop;
} OwnedEntry;

typedef struct RecordEntry {
    u16 rank : 2;
    u16 : 14;
    u16 active : 1;
    u16 level : 7;
} RecordEntry;

typedef struct RowWidgets {
    s16 frame;
    s16 cursor;
    s16 soldOut;
    s16 status;
    s16 maxed;
    s16 locked;
} RowWidgets;

typedef struct PriceRange {
    u16 high;
    u16 low;
    u8 pad_04[8];
} PriceRange;

typedef struct ItemList {
    s16 count;
    s16 cursor;
    s16 top;
    u8 pad_06;
    u8 visibleRows;
} ItemList;

typedef struct ShopMenu {
    u8 mode;
    u8 dirty;
    u8 useCatalog;
    s8 tab;
    u8 quantity;
    u8 maxQuantity;
    u8 pickerOpen;
    u8 pad_07;
    int confirmed;
    u8 pad_0c[4];
    s16 itemId;
    u8 pad_12[2];
    int unitPrice;
    u8 pad_18[4];
    ItemList list;
    u8 pad_24[0x1a8];
    void *records;
    void *layout;
    int *tabWidgets[10];
    u8 pad_1fc[8];
    int *tabFrame;
    int *pairWidgets[2];
    int *maxedWidget;
    RowWidgets rows[7];
    u8 pad_268[0x1c];
    PriceRange ranges[0x458];
    ItemEntry *catalog[0x45b];
    u8 images[0x123c];
    OwnedEntry *slots[0x102];
} ShopMenu;

typedef struct StockSlot {
    u16 itemId;
    u16 pad_02;
} StockSlot;

typedef struct SaveData {
    u8 pad_0000[0x28d0];
    int munny;
    u8 pad_28d4[4];
    u8 itemCounts[0x390];
    u8 stockCount;
    u8 pad_2c69[0x11b];
    StockSlot stock[15];
    int stockAmounts[15];
} SaveData;

extern SaveData *data_0205fe0c;
extern const s8 data_ov085_020c22c4[];

extern void func_0204f378(void *layout, int index, int value);
extern int *FindWidgetById_020b90a4(void *root, int id);
extern void SetEntrySlotsVisible_020b9580(void *layout, int *widget, int visible);
extern void func_ov039_020bdf10(ItemList *list, void *layout, int animate);
extern BOOL func_ov085_020bf754(ShopMenu *menu, int index, RecordEntry *record);
extern void ReleaseRecordEntry_02029388(u16 recordId);
extern void func_02029240(int itemId, RecordEntry *record);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern u32 func_ov039_020bc7f8(void);
extern void func_ov001_020645dc(int bitOffset);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u16 FilterItemsForTab_020c14c0(ShopMenu *menu, int kind);
extern void MoveTabCursor_020c1164(ShopMenu *menu, int tab);
extern void ResetCursorPosition_020c1550(ShopMenu *menu);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void PushPendingPair_020bf614(int first, int second);
extern u16 GetSecondaryRecordCount_020291c0(void);
extern u32 func_020291b4(void);
extern void ArrangeWidgetPair_020c0b38(ShopMenu *menu);

static inline PriceRange *GetPriceRange(ShopMenu *menu, int id)
{
    return &menu->ranges[id];
}

static inline int ClampedSum(int delta, int base)
{
    int result = base + delta;

    if (result < 0) {
        result = 0;
    } else if (result > 999999) {
        result = 999999;
    }
    return result;
}

void SetShopMenuMode_020c0b90(ShopMenu *menu, u8 nextMode)
{
    s16 i;
    s16 j;
    void *layout = menu->layout;
    void *records = menu->records;

    switch (menu->mode) {
    case 0: {
        for (i = 0; i < 7; i++) {
            func_0204f378(layout, menu->rows[i].frame, 0);
            func_0204f378(layout, menu->rows[i].cursor, 0);
            func_0204f378(layout, menu->rows[i].soldOut, 0);
            func_0204f378(layout, menu->rows[i].maxed, 0);
            func_0204f378(layout, menu->rows[i].locked, 0);
            func_0204f378(layout, menu->rows[i].status, 0);
        }
        for (j = 0; j < 10; j++) {
            if (menu->tabWidgets[j]) {
                SetEntrySlotsVisible_020b9580(layout, menu->tabWidgets[j], 0);
            }
        }
        SetEntrySlotsVisible_020b9580(layout, menu->tabFrame, 0);
        func_ov039_020bdf10(&menu->list, layout, 0);
        break;
    }
    case 2: {
        RecordEntry *recordPtr = NULL;
        s16 count;

        SetEntrySlotsVisible_020b9580(layout, menu->pairWidgets[0], 0);
        SetEntrySlotsVisible_020b9580(layout, menu->pairWidgets[1], 0);
        if (menu->pickerOpen) {
            SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x17), 0);
            if (nextMode == 0) {
                SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x16), 0);
            }
            break;
        }
        if (menu->useCatalog) {
            ItemEntry *entry = menu->catalog[(u16)menu->list.cursor];

            if (menu->itemId >= 0 && menu->itemId <= 0x7f) {
                ReleaseRecordEntry_02029388(entry->recordId);
                GetPriceRange(menu, entry->info->id)->high -= menu->quantity;
            } else {
                data_0205fe0c->itemCounts[menu->itemId] -= menu->quantity;
                entry->total -= menu->quantity;
            }
            data_0205fe0c->munny = ClampedSum(menu->quantity * menu->unitPrice, data_0205fe0c->munny);
        } else {
            RecordEntry record;
            OwnedEntry *slot = menu->slots[menu->list.cursor];
            u16 n;

            if (func_ov085_020bf754(menu, menu->list.cursor, &record)) {
                recordPtr = &record;
            }
            for (n = menu->quantity; n != 0; n--) {
                func_02029240(menu->itemId, recordPtr);
            }
            SetGlobalPackedBit_02027320(menu->itemId);
            GetPriceRange(menu, menu->itemId)->high += menu->quantity;
            *slot->count += menu->quantity;
            data_0205fe0c->munny = ClampedSum(-(menu->quantity * menu->unitPrice), data_0205fe0c->munny);

            if (func_ov039_020bc7f8() & 0x8000) {
                func_ov001_020645dc(0x35e4);
            }
        }
        PlaySoundEffect_0204d924(0, 0x3c);
        count = FilterItemsForTab_020c14c0(menu, data_ov085_020c22c4[menu->tab]);
        if (count == 0) {
            menu->tab = 0;
            FilterItemsForTab_020c14c0(menu, -1);
            MoveTabCursor_020c1164(menu, menu->tab);
            ResetCursorPosition_020c1550(menu);
        } else if (menu->list.count > count) {
            menu->list.count = count;
            if (menu->list.top + menu->list.visibleRows > count) {
                s16 shift = menu->list.visibleRows < count ? menu->list.top + menu->list.visibleRows - count
                                                           : menu->list.top;

                menu->list.top -= shift;
                menu->list.cursor -= shift;
            }
            if (menu->list.cursor >= count) {
                int last = 0;

                if (count != 0) {
                    last = count - 1;
                }
                menu->list.cursor = last;
            }
            func_ov039_020bdf10(&menu->list, menu->layout, 1);
        }
    }
    case 1:
        if (nextMode != 2) {
            SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x16), 0);
            InvokeCallback40_020b8268(records, FindActiveRecordById_020b8184(records, 2));
        }
        SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x17), 0);
        break;
    }

    switch (nextMode) {
    case 0: {
        i = 0;
        do {
            func_0204f378(layout, menu->rows[i].frame, 1);
            func_0204f378(layout, menu->rows[i].cursor, 1);
            if (!menu->useCatalog) {
                OwnedEntry *slot = menu->slots[menu->list.cursor];
                int soldOut = 0;

                if (*slot->count != 0 && *slot->count >= slot->shop->stockLimit) {
                    soldOut = 1;
                }
                func_0204f378(layout, menu->rows[i].soldOut, soldOut);
            }
            i++;
        } while (i < 7);
        j = 0;
        do {
            if (menu->tabWidgets[j]) {
                SetEntrySlotsVisible_020b9580(layout, menu->tabWidgets[j], 1);
            }
            j++;
        } while (j < 10);
        SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x17), 0);
        SetEntrySlotsVisible_020b9580(layout, menu->tabFrame, 1);
        SetEntrySlotsVisible_020b9580(menu->layout, menu->maxedWidget, 0);
        func_ov039_020bdf10(&menu->list, layout, 1);
        MoveTabCursor_020c1164(menu, menu->tab);
        PushPendingPair_020bf614(0, 0);
        break;
    }
    case 1:
        if (menu->mode != 2) {
            u32 byStock;
            u32 byMoney;
            u32 byCount;

            if (menu->useCatalog) {
                int k;
                u16 *stock;

                k = data_0205fe0c->stockCount + 2;
                stock = &data_0205fe0c->stock[0].itemId;
                byStock = 99;
                byCount = data_0205fe0c->itemCounts[menu->itemId];
                byMoney = 99;
                do {
                    if (menu->itemId == stock[k * 2]) {
                        byCount -= data_0205fe0c->stockAmounts[k];
                    }
                    k--;
                } while (k >= 0);
            } else {
                OwnedEntry *slot = menu->slots[menu->list.cursor];

                if (slot->shop->stockLimit == 0) {
                    byStock = 99;
                } else {
                    byStock = slot->shop->stockLimit - *slot->count;
                }
                if (slot->entry->info->id >= 0 && slot->entry->info->id <= 0x7f) {
                    byCount = GetSecondaryRecordCount_020291c0() - func_020291b4();
                    if (byCount > 99) {
                        byCount = 99;
                    }
                } else {
                    byCount = 99 - data_0205fe0c->itemCounts[menu->itemId];
                }
                byMoney = (u32)data_0205fe0c->munny / menu->unitPrice;
            }
            SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x16), 1);
            TagTracker_InvokeCallback_020b8210(records, FindActiveRecordById_020b8184(records, 2));
            if (byMoney >= byCount) {
                byMoney = byCount;
            }
            if (byStock < byMoney) {
                byMoney = byStock;
            }
            menu->quantity = 1;
            if (byMoney >= 99) {
                byMoney = 99;
            }
            menu->maxQuantity = byMoney;
            if (menu->maxQuantity != 1) {
                PushPendingPair_020bf614(3, data_0205fe0c->itemCounts[menu->itemId] + 1);
                SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x17), 1);
                break;
            }
            menu->confirmed = 1;
            nextMode = 2;
        } else {
            SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x17), 1);
            break;
        }
    case 2:
        if (menu->confirmed) {
            menu->quantity = 1;
            menu->maxQuantity = 1;
            SetEntrySlotsVisible_020b9580(layout, FindWidgetById_020b90a4(layout, 0x16), 1);
            TagTracker_InvokeCallback_020b8210(records, FindActiveRecordById_020b8184(records, 2));
        }
        SetEntrySlotsVisible_020b9580(layout, menu->pairWidgets[0], 1);
        SetEntrySlotsVisible_020b9580(layout, menu->pairWidgets[1], 1);
        menu->pickerOpen = 1;
        ArrangeWidgetPair_020c0b38(menu);
        break;
    }
    menu->mode = nextMode;
    menu->dirty = 1;
}

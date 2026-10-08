#pragma opt_dead_assignments off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TextLayer {
    u8 data[0x34];
} TextLayer;

typedef struct ItemInfo {
    int id;
    u8 pad_04[8];
    u32 basePrice;
    int iconId;
    u8 pad_14[0x30];
    const u16 *name;
} ItemInfo;

typedef struct ItemEntry {
    u16 total;
    u16 used;
    s16 recordId;
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
    s16 soldOut;
    s16 status;
    s16 maxed;
    s16 locked;
    u8 pad_08[4];
} RowWidgets;

typedef struct PriceRange {
    u16 high;
    u16 low;
    u8 pad_04[8];
} PriceRange;

typedef struct Widget {
    u8 pad_00[0x14];
    int index;
} Widget;

typedef struct ItemMenu {
    u8 mode;
    u8 dirty;
    u8 useCatalog;
    u8 pad_03;
    u8 quantity;
    u8 pad_05[0xb];
    s16 itemId;
    u8 pad_12[2];
    int unitPrice;
    u8 pad_18[4];
    s16 count;
    s16 cursor;
    s16 top;
    u8 pad_22;
    u8 visibleRows;
    u8 pad_24[0xcc];
    TextLayer layers[4];
    u8 pad_1c0[4];
    const u16 *currencyText;
    const u16 *ownedText;
    u8 pad_1cc[4];
    void *layout;
    u8 pad_1d4[0x3c];
    int *maxedWidget;
    u8 pad_214[4];
    RowWidgets rows[6];
    u8 pad_260[8];
    s16 rowIcons[7];
    s16 detailIcon;
    u8 strings[0xc];
    PriceRange ranges[0x458];
    ItemEntry *catalog[0x45b];
    u8 images[0x123c];
    OwnedEntry *slots[0x102];
    int seenBits[0x10];
    int *ownedBits;
} ItemMenu;

extern u8 *data_0205fe0c;
extern const u16 data_ov085_020c239c[];
extern const u16 data_ov085_020c23a4[];
extern u8 data_0205a92c[];
extern u8 data_0205a970[];
typedef struct CameraState {
    u8 pad_000[0xd4];
    u32 dirtyFlags;
    u8 pad_0d8[0x218 - 0xd8];
    VecFx32 camPos;
    VecFx32 camUp;
    VecFx32 camTarget;
} CameraState;

extern CameraState data_0205a924;

extern int func_ov039_020bc97c(void);
extern int func_ov039_020bc994(void);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void MIi_CpuFill8_01ff8830(void *dest, u8 data, u32 size);
extern Widget *FindWidgetById_020b90a4(void *root, int id);
extern void func_ov027_020b97b8(void *context, Widget *record, int mode);
extern void func_0204f204(void *layout, int index, u16 value);
extern void func_0204f2e4(void *layout, int index);
extern void func_0204f378(void *layout, int index, int value);
extern ItemInfo *func_ov085_020bf700();
extern ItemEntry *GetItemMenuEntry_020bf72c(ItemMenu *menu, int index);
extern BOOL func_ov085_020bf754(ItemMenu *menu, int index, RecordEntry *record);
extern void SetPackedBit_0202d44c(int *bitWords, int bitIndex);
extern int GetPackedBitMask_0202d4a0(int *bitWords, int bitIndex);
extern BOOL CanSelectItem_020c138c(ItemMenu *menu, int index);
extern void DrawItemNameWithRank_020c11e8(ItemMenu *menu, int index, int x, int y, int color);
extern int FormatStateText_020bccac(int id, u16 *buffer, int format, ...);
extern void DrawTextAnchored_020015a0(TextLayer *obj, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextColored_02001668(TextLayer *obj, int x, int y, int color, int altColor, const u16 *text);
extern void Obj_SetField14_02001490(TextLayer *obj, int value);
extern void *func_ov027_020ba2a8(void *strings, int index);
extern u16 *func_ov085_020c1354(ItemMenu *menu, int index, u16 *buffer);
extern int func_ov085_020c1304(ItemEntry *entry);
extern void SetEntrySlotsVisible_020b9580(void *layout, int *widget, int visible);
extern int OS_SNPrintf_0202e080(u16 *dst, u32 len, const u16 *fmt, ...);
extern void PushPendingPair_020bf614(int first, int second);
extern void SetSharedStateValue_020bf638(void *value);
extern void Text_UploadTileBuffer_02001520(TextLayer *surface);
extern void MTX_OrthoW_02005f10(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scaleW,
                                void *projOut);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, void *viewOut);
extern void DrawIndexedImageQuad_020c2140(void *images, u32 indexColor, u32 pos, fx32 depth);

static inline PriceRange *GetPriceRange(ItemMenu *menu, int id)
{
    return &menu->ranges[id];
}

#define MUNNY (*(int *)(data_0205fe0c + 0x28d0))

void RedrawShopMenu_020c0280(ItemMenu *menu)
{
    VecFx32 up;
    VecFx32 target;
    VecFx32 pos;
    u32 rowCount;
    u16 i;

    if (menu->dirty) {
        void *tip = NULL;
        int normalColor = func_ov039_020bc97c();
        int dimColor = func_ov039_020bc994();
        Widget *widget;

        CallVirtualHandlerSlot1_02001574(&menu->layers[2], 0);
        CallVirtualHandlerSlot1_02001574(&menu->layers[3], 0);
        MIi_CpuFill8_01ff8830(menu->rowIcons, 0xff, sizeof(menu->rowIcons));
        menu->detailIcon = -1;
        widget = FindWidgetById_020b90a4(menu->layout, 0xd);
        func_ov027_020b97b8(menu->layout, widget, 2);
        func_0204f204(menu->layout, widget->index, 1);
        func_0204f2e4(menu->layout, widget->index);

        switch (menu->mode) {
        case 0:
            if (menu->cursor < menu->count) {
                s16 index = menu->top;
                s16 remaining = menu->visibleRows;
                s16 y = 3;
                s16 row = 0;
                int shownId = func_ov085_020bf700(menu)->id;

                SetPackedBit_0202d44c(menu->seenBits, shownId);
                do {
                    ItemEntry *entry = GetItemMenuEntry_020bf72c(menu, index);
                    int soldOut = 0;
                    int maxed = 0;
                    int locked = 0;
                    int status;

                    if (entry != NULL) {
                        int color = CanSelectItem_020c138c(menu, index) ? 2 : 4;
                        RecordEntry record;
                        u16 buffer[0x30];
                        int itemId;
                        BOOL owned;
                        BOOL seen;

                        DrawItemNameWithRank_020c11e8(menu, index, 3, y, color);
                        if (func_ov085_020bf754(menu, index, &record)) {
                            maxed = record.level == 100 ? 1 : 0;
                            if (!maxed && record.level != 0) {
                                FormatStateText_020bccac(1, buffer, 8, record.level);
                                DrawTextAnchored_020015a0(&menu->layers[2], 0x7b, y, color, 0x20, buffer);
                            }
                        }
                        if (menu->useCatalog == 0) {
                            OwnedEntry *slot = menu->slots[index];
                            int limit = slot->shop->stockLimit;

                            soldOut = (limit != 0 && *slot->count >= limit) ? 1 : 0;
                            if (menu->cursor == index && limit != 0) {
                                tip = func_ov027_020ba2a8(menu->strings, 0x1e);
                            }
                        } else {
                            locked = entry->used != 0 ? 1 : 0;
                        }
                        if (menu->useCatalog || !soldOut) {
                            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, y, color, 0x20,
                                                      func_ov085_020c1354(menu, index, buffer));
                            Obj_SetField14_02001490(&menu->layers[2], normalColor);
                            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, y + 2, 10, 8, menu->currencyText);
                            Obj_SetField14_02001490(&menu->layers[2], dimColor);
                        }
                        menu->rowIcons[row] = entry->info->iconId;
                        itemId = entry->info->id;
                        owned = GetPackedBitMask_0202d4a0(menu->ownedBits, itemId) ? 1 : 0;
                        seen = GetPackedBitMask_0202d4a0(menu->seenBits, itemId) ? 1 : 0;
                        if (owned) {
                            status = 2;
                        } else {
                            status = seen ? 1 : 0;
                        }
                    } else {
                        menu->rowIcons[row] = -1;
                        status = 2;
                    }
                    func_0204f378(menu->layout, menu->rows[row].soldOut, soldOut);
                    func_0204f378(menu->layout, menu->rows[row].status, status < 2);
                    func_0204f378(menu->layout, menu->rows[row].maxed, maxed);
                    func_0204f378(menu->layout, menu->rows[row].locked, locked);
                    if (status < 2) {
                        func_0204f204(menu->layout, menu->rows[row].status, status);
                    }
                    index++;
                    row++;
                    remaining--;
                    y += 16;
                } while (index < menu->count && remaining > 0);

                while (row < menu->visibleRows) {
                    func_0204f378(menu->layout, menu->rows[row].soldOut, 0);
                    func_0204f378(menu->layout, menu->rows[row].maxed, 0);
                    func_0204f378(menu->layout, menu->rows[row].locked, 0);
                    func_0204f378(menu->layout, menu->rows[row].status, 0);
                    menu->rowIcons[row++] = -1;
                }
            }
            break;
        case 2:
            DrawTextAnchored_020015a0(&menu->layers[2], 0x68, 0x4b, 2, 0x10,
                                      func_ov027_020ba2a8(menu->strings, menu->useCatalog ? 0x11 : 0x10));
            DrawTextAnchored_020015a0(&menu->layers[2], 0x2c, 0x5b, 2, 0x10, func_ov027_020ba2a8(menu->strings, 0x12));
            DrawTextAnchored_020015a0(&menu->layers[2], 0x90, 0x5b, 2, 0x10, func_ov027_020ba2a8(menu->strings, 0x13));
        case 1: {
            s16 index = menu->cursor;
            ItemInfo *info = GetItemMenuEntry_020bf72c(menu, index)->info;
            RecordEntry record;
            u16 buffer[0x30];
            int total;
            int delta;
            int after;
            int color;

            DrawItemNameWithRank_020c11e8(menu, index, 0x10, 0x13, 2);
            DrawTextAnchored_020015a0(&menu->layers[2], 0x10, 0x23, 2, 8, menu->ownedText);
            if (func_ov085_020bf754(menu, index, &record)) {
                BOOL maxed = TRUE;
                if (record.level != 100) {
                    maxed = FALSE;
                }
                SetEntrySlotsVisible_020b9580(menu->layout, menu->maxedWidget, maxed);
                if (!maxed && record.level != 0) {
                    FormatStateText_020bccac(1, buffer, 8, record.level);
                    DrawTextAnchored_020015a0(&menu->layers[2], 0x74, 0x13, 2, 0x20, buffer);
                }
            }
            Obj_SetField14_02001490(&menu->layers[2], normalColor);
            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, 0x15, 10, 8, menu->currencyText);
            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, 0x25, 10, 8, menu->currencyText);
            DrawTextAnchored_020015a0(&menu->layers[2], 0x58, 0x3a, 10, 8, menu->currencyText);
            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, 0x3a, 10, 8, menu->currencyText);
            Obj_SetField14_02001490(&menu->layers[2], dimColor);
            menu->detailIcon = info->iconId;
            OS_SNPrintf_0202e080(buffer, 8, data_ov085_020c239c, menu->quantity);
            DrawTextAnchored_020015a0(&menu->layers[2], 0x60, 0x23, 2, 8, data_ov085_020c23a4);
            DrawTextAnchored_020015a0(&menu->layers[2], 0x74, 0x23, 2, 0x20, buffer);
            total = menu->unitPrice * menu->quantity;
            delta = menu->useCatalog ? total : -total;
            after = MUNNY + delta;
            if (after > 999999) {
                after = 999999;
            }
            color = 8;
            OS_SNPrintf_0202e080(buffer, 8, data_ov085_020c239c, menu->unitPrice);
            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, 0x13, 2, 0x20, buffer);
            OS_SNPrintf_0202e080(buffer, 8, data_ov085_020c239c, total);
            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, 0x23, 2, 0x20, buffer);
            OS_SNPrintf_0202e080(buffer, 8, data_ov085_020c239c, MUNNY);
            DrawTextAnchored_020015a0(&menu->layers[2], 0x58, 0x38, 2, 0x20, buffer);
            OS_SNPrintf_0202e080(buffer, 8, data_ov085_020c239c, after);
            if (menu->useCatalog) {
                color = 0xc;
            }
            DrawTextAnchored_020015a0(&menu->layers[2], 0xa0, 0x38, color, 0x20, buffer);
            PushPendingPair_020bf614(1, after);
            PushPendingPair_020bf614(3, (data_0205fe0c + menu->itemId)[0x28d8] +
                                            (menu->useCatalog ? -menu->quantity : menu->quantity));
            if (menu->mode == 1) {
                tip = func_ov027_020ba2a8(menu->strings, 0x14);
            }
            break;
        }
        }

        if (menu->count > 0) {
            s16 index = menu->cursor;
            ItemInfo *info = func_ov085_020bf700(menu, index);
            ItemEntry *entry = GetItemMenuEntry_020bf72c(menu, index);
            PriceRange *range;

            DrawTextColored_02001668(&menu->layers[3], 2, 0, 2, 10, info->name);
            menu->itemId = info->id;
            if (menu->useCatalog) {
                menu->unitPrice = func_ov085_020c1304(entry);
            } else {
                menu->unitPrice = menu->slots[index]->shop->price;
            }
            range = GetPriceRange(menu, info->id);
            PushPendingPair_020bf614(2, range->low | (u16)(range->high - range->low) << 16);
        }
        Text_UploadTileBuffer_02001520(&menu->layers[2]);
        Text_UploadTileBuffer_02001520(&menu->layers[3]);
        Text_UploadTileBuffer_02001520(&menu->layers[0]);
        Text_UploadTileBuffer_02001520(&menu->layers[1]);
        SetSharedStateValue_020bf638(tip);
        menu->dirty--;
    }

    rowCount = menu->visibleRows;
    MTX_OrthoW_02005f10(0xc0000, 0, 0, 0x100000, 0, 0x400000, 0x200000, data_0205a92c);
    data_0205a924.dirtyFlags &= ~0x50;
    pos.z = 0x400000;
    pos.y = 0;
    pos.x = 0;
    target.z = 0;
    target.y = 0;
    target.x = 0;
    up.z = 0;
    up.x = 0;
    up.y = 0x1000;
    data_0205a924.camPos = pos;
    data_0205a924.camUp = up;
    data_0205a924.camTarget = target;
    func_01ff9b70(&pos, &up, &target, data_0205a970);
    data_0205a924.dirtyFlags &= ~0xe8;

    if (menu->detailIcon >= 0) {
        DrawIndexedImageQuad_020c2140(menu->images, (u16)menu->detailIcon << 16 | 0x7fff, 0x1d0038, 0x3fe);
    }
    for (i = 0; i < rowCount; i++) {
        if (menu->rowIcons[i] >= 0) {
            DrawIndexedImageQuad_020c2140(menu->images, (u16)menu->rowIcons[i] << 16 | 0x7fff,
                                          0x100000 | (u16)(s16)(i * 16 + 0x28), 0x3fe);
        }
    }
}

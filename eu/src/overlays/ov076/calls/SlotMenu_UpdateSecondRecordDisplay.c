#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SlotItem {
    s32 x;
    s32 y;
    BOOL enabled;
    s32 spriteId;
    s32 variation;
    s32 handle;
} SlotItem;

typedef struct SlotView {
    SlotItem items[18];
} SlotView;

typedef struct LabelSource {
    u8 unknown00[8];
    u32 progressLimit;
} LabelSource;

typedef struct LabelEntry {
    LabelSource *source;
    u8 unknown04[8];
} LabelEntry;

typedef struct SlotMenu {
    u8 unknown00000[0x824];
    LabelEntry labels[256];
    u8 unknown01424[0x1b914 - 0x1424];
    SlotView slots[8];
} SlotMenu;

typedef char RecordEntryIsFourBytes[sizeof(RecordEntry) == 4 ? 1 : -1];
typedef char SlotItemIs24Bytes[sizeof(SlotItem) == 24 ? 1 : -1];
typedef char SlotViewIs432Bytes[sizeof(SlotView) == 0x1b0 ? 1 : -1];
typedef char LabelEntryIs12Bytes[sizeof(LabelEntry) == 12 ? 1 : -1];
typedef char SlotMenuLabelsOffset[(u32)&((SlotMenu *)0)->labels == 0x824 ? 1 : -1];
typedef char SlotMenuSlotsOffset[(u32)&((SlotMenu *)0)->slots == 0x1b914 ? 1 : -1];
typedef char ProgressLimitOffset[(u32)&((LabelSource *)0)->progressLimit == 8 ? 1 : -1];

extern void SlotMenu_DrawRecordLabel(SlotMenu *menu, int slot, int part, const RecordEntry *record);

/* Update the second record's digits, progress gauge, variant icon and level badge. */
void SlotMenu_UpdateSecondRecordDisplay(SlotMenu *menu, int slot, const RecordEntry *record, int resetProgress)
{
    u32 rowByteOffset = slot;
    rowByteOffset *= sizeof(SlotView);
    SlotView *view = (SlotView *)((u8 *)menu->slots + rowByteOffset);
    u32 variant = record->variant;
    u32 progress;
    u32 limit;
    int gauge;

    if (variant == 0) {
        u16 category = (u16)record->category;
        u16 entryStride = sizeof(LabelEntry);
        category = (u8)category;
        int labelByteOffset = entryStride * category;
        limit = ((LabelEntry *)((u8 *)menu->labels + labelByteOffset))->source->progressLimit;
        if (resetProgress != 0) {
            progress = 0;
        } else {
            progress = record->levelProgress;
        }
        view->items[7].enabled = progress / 1000 != 0;
        view->items[7].variation = progress / 1000;
        view->items[8].enabled = progress / 100 != 0;
        view->items[8].variation = progress / 100 % 10;
        view->items[9].enabled = progress / 10 != 0;
        view->items[9].variation = progress / 10 % 10;
        view->items[10].enabled = TRUE;
        view->items[10].variation = progress % 10;
        view->items[12].enabled = TRUE;
        view->items[11].enabled = TRUE;
        gauge = 0;
        if (progress != 0) {
            gauge = ((0xd000 * progress / limit) >> 12) + 1;
        }
        if (gauge >= 14) {
            gauge = 14;
        }
        view->items[11].variation = gauge;
    } else {
        view->items[17].enabled = TRUE;
        view->items[17].variation = variant - 1;
    }
    if (record->level == 100) {
        view->items[14].enabled = TRUE;
    }
    SlotMenu_DrawRecordLabel(menu, slot, 1, record);
}

#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 pad_01[0xb];
} InfoEntry;

typedef struct {
    u8 pad_00[4];
    s8 infoIndex;
} SlotEntry;

typedef struct {
    u8 slotIndex;
    u8 isActive;
    u8 pad_02[0x2e];
} ItemEntry;

typedef struct {
    u32 unk_00;
    InfoEntry *infos;
    ItemEntry *items;
    SlotEntry *slots[1];
} ItemContext;

extern ItemContext *func_ov001_020689a4(void);

BOOL func_ov040_020bcc24(int itemIndex) {
    ItemContext *context = func_ov001_020689a4();
    ItemEntry *item = &context->items[itemIndex];
    if (item->isActive != 0) {
        return TRUE;
    }
    if (context->infos[context->slots[item->slotIndex]->infoIndex].kind == 0x37) {
        return TRUE;
    }
    return FALSE;
}

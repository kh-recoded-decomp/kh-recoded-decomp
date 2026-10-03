#include "nitro/types.h"

typedef struct {
    s32 id;
    s32 kind;
} ItemDef;

typedef struct {
    u8 pad_00[4];
    s16 recordIndex;
    u16 pad_06;
    ItemDef *def;
} ItemSlot;

typedef struct {
    u8 pad_00[0x3c18];
    ItemSlot *slots[0x45b];
    s16 slotCount;
    s16 cursor;
    u8 pad_4d88[0x7f94 - 0x4d88];
    s32 currentId;
    s16 currentIndex;
    u8 pad_7f9a[0x11e24 - 0x7f9a];
    u8 idCount;
    u8 pad_11e25[3];
    u32 ids[1];
} ItemPicker;

extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void CloseItemPicker_020cde4c(ItemPicker *picker, BOOL closing);
extern BOOL IsItemSlotAvailable_020cdf10(ItemSlot *slot, u32 count, u32 *ids);

s32 ConfirmItemPicker_020ceb78(ItemPicker *picker)
{
    BOOL current;
    ItemDef *def;
    ItemSlot *slot;
    BOOL selectable;

    if (picker->cursor < picker->slotCount) {
        selectable = FALSE;
        current = FALSE;
        slot = picker->slots[picker->cursor];
        def = slot->def;
        if (def->id == picker->currentId && slot->recordIndex == picker->currentIndex) {
            current = TRUE;
        }
        if (current) {
            switch (def->kind) {
            case 0:
            case 2:
            case 3:
                selectable = TRUE;
                break;
            }
        }
        if (IsItemSlotAvailable_020cdf10(slot, picker->idCount, picker->ids)) {
            selectable = TRUE;
        }
        if (selectable) {
            CloseItemPicker_020cde4c(picker, TRUE);
            return 2;
        }
    }
    PlaySoundEffect_0204d924(1, 4);
    return 1;
}

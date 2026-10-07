#include "nitro/types.h"

typedef struct ItemStock {
    u8 data[12];
} ItemStock;

typedef struct ItemListMenu {
    u8 pad_0000[0x7f8];
    ItemStock stocks[];
} ItemListMenu;

typedef struct ItemRecordRef {
    u16 kind;
    volatile u16 slotFlags : 8;
    volatile u16 stockIndex : 8;
} ItemRecordRef;

ItemStock *MatrixMenu_GetStockForRecord_020d0f34(ItemListMenu *menu, const ItemRecordRef *record)
{
    u8 index = record->stockIndex;

    return (ItemStock *)((u8 *)menu + 0x7f8 + index * sizeof(ItemStock));
}

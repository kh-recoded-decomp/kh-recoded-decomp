#pragma opt_propagation off
#include "nitro/types.h"

typedef struct SlotMenuRow {
    u8 reserved00[4];
    s16 recordIndex;
} SlotMenuRow;

typedef struct SlotMenu {
    u8 reserved00000[0x14];
    s32 column;
    u8 reserved00018[0x3c3c - 0x18];
    SlotMenuRow *rows[1];
    u8 reserved03c40[0x4daa - 0x3c40];
    s16 cursorRow;
    u8 reserved04dac[0x11ee6 - 0x4dac];
    s16 slotIndex;
} SlotMenu;

typedef struct SaveData {
    u8 reserved0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;

static inline BOOL IsMatchingRecord(s16 recordIndex, u32 handle)
{
    BOOL isRecord = FALSE;
    BOOL result = FALSE;
    if (recordIndex >= 0 && (u16)handle >= 0x200 && (u16)handle < 0x458) {
        isRecord = TRUE;
    }
    if (isRecord && recordIndex == handle - 0x200) {
        result = TRUE;
    }
    return result;
}

BOOL SlotMenu_IsSelectedRecordEquipped_020c51cc(SlotMenu *menu)
{
    SlotMenuRow *row = menu->rows[menu->cursorRow];
    int column = menu->column;
    BOOL result;
    if (column < 2) {
        u16 handle = data_0205fe0c->slotHandles[menu->slotIndex * 2 + column];
        result = IsMatchingRecord(row->recordIndex, handle);
    } else {
        result = FALSE;
    }
    return result;
}
